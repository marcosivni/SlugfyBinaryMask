#include <QApplication>
#include <QByteArray>

#include <iostream>

#include <PngLib.h>
#include <BasicArrayObject.h>

std::string serialize(std::string file){

    std::string answer;
    PNGImage *image = new PNGImage(file);
    unsigned char *serialized = new unsigned char[sizeof(uint32_t) + sizeof(uint32_t) +  (sizeof(bool) * image->getWidth()*image->getHeight())];

    uint32_t size = image->getWidth();
    memcpy(serialized, &size, sizeof(uint32_t));
    size = image->getHeight();
    memcpy(serialized + sizeof(uint32_t), &size, sizeof(uint32_t));

    for (uint32_t x = 0; x < image->getHeight(); x++){
        for (uint32_t y = 0; y < image->getWidth(); y++){
            bool aux = 0;
            if ( image->getPixel(y,x).getGrayPixelValue() == 255 ){
                aux = 1;
            }
            memcpy(serialized + (2*sizeof(uint32_t))+(sizeof(bool)*((x*image->getWidth()) + y)), &aux, sizeof(bool));
        }
    }

    for (unsigned long x = 0; x < sizeof(uint32_t) + sizeof(uint32_t) +  (sizeof(bool)*image->getWidth()*image->getHeight()); x++){
        answer += serialized[x];
    }

    delete[] (serialized);
    delete (image);

    return answer;
}

Image unserialize(std::string dataIn){

    uint32_t w, h;
    bool *d;

    memcpy(&w, dataIn.c_str(), sizeof(uint32_t));
    memcpy(&h, dataIn.c_str() + sizeof(uint32_t), sizeof(uint32_t));

    Image bmp;
    bmp.createPixelMatrix(w, h);
    d = new bool[w*h];

    for (uint32_t x = 0; x < bmp.getHeight(); x++){
        for (uint32_t y = 0; y < bmp.getWidth(); y++){
            memcpy(&d[(x*bmp.getWidth()) + y], dataIn.c_str() + sizeof(uint32_t) + sizeof(uint32_t) + (sizeof(bool)*( (x*bmp.getWidth()) + y)), sizeof(bool));
            Pixel p;
            if (d[(x*bmp.getWidth()) + y]){
                p.setGrayPixelValue(255);
            }
            bmp.setPixel(y, x, p);
        }
    }

    delete[] (d);

    return bmp;
}

QString readAndCompressMask(std::string file){

    std::string s = serialize(file);
    QString conversor = FeatureVector::toBase64(s).c_str();
    QByteArray byteArray(conversor.toUtf8());
    byteArray = qCompress(byteArray, 9);
    QString zipStr = QString::fromUtf8(byteArray.toBase64().data(), byteArray.toBase64().size());

    return zipStr;
}

Image uncompressMask(QString zipStr){

    QByteArray byteArray = QByteArray::fromBase64(QByteArray(zipStr.toUtf8()));
    QString result;
    std::string answer;

    byteArray = qUncompress(byteArray);

    result = QString::fromUtf8(byteArray.data(), byteArray.size());
    answer = FeatureVector::fromBase64(result.toStdString());
    return unserialize(answer);
}

int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    std::string filename;
    std ::cin >> filename;

    std::cout << filename.c_str() << ", ";
    std::cout << readAndCompressMask(filename).toStdString() << std::endl;
    std::cin >> filename;

    return a.exec();
}
