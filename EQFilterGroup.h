#ifndef EQFILTERGROUP_H
#define EQFILTERGROUP_H

#include <QAudioBuffer>
#include <QBuffer>
#include <QByteArray>
#include <QVector>

class EQFilterGroup
{
public:
    EQFilterGroup();
    void setLowGain(float gain){_low_gain = gain;}
    void setMidGain(float gain){_mid_gain = gain;}
    void setHighGain(float gain){_high_gain = gain;}

    template<class T>
    void decode_channel(QVector<float>& channel1, QVector<float>& channel2, QAudioBuffer const& buffer)
    {
        T* data = (T*)(buffer.data());
        size_t len = buffer.sampleCount();

        for (size_t i=0; i < len; i+=2) {
            T left = data[i];
            T right = data[i+1];

            left = std::isnan(left) ? 0.0 : left;
            right = std::isnan(right) ? 0.0 : right;

            channel1.append(float(left) / std::numeric_limits<T>::max());
            channel2.append(float(right)/ std::numeric_limits<T>::max());
        }
    }

    template<class T>
    void encode_channel(QVector<float> const& channel1, QVector<float> const& channel2, QByteArray& bytes)
    {
        for(size_t i = 0; i < channel1.count() && i < channel2.count(); ++i){
            float left = channel1[i] > 1.0 ? 1.0 : channel1[i];
            float right = channel2[i] > 1.0 ? 1.0 : channel2[i];

            T lpcm = T(std::floor(left * std::numeric_limits<T>::max()));
            T rpcm = T(std::floor(right * std::numeric_limits<T>::max()));
            bytes.append((char*)&lpcm, sizeof(lpcm));
            bytes.append((char*)&rpcm, sizeof(rpcm));
        }
    }

    QBuffer* filter(QAudioBuffer const& buffer);
    float low_band_filter_channel1(float invar, float initval, int setic);
    float low_band_filter_channel2(float invar, float initval, int setic);

    float mid_band_filter_channel1(float invar, float initval, int setic);
    float mid_band_filter_channel2(float invar, float initval, int setic);

    float high_band_filter_channel1(float invar, float initval, int setic);
    float high_band_filter_channel2(float invar, float initval, int setic);

private:
    float _low_gain;
    float _mid_gain;
    float _high_gain;
};

#endif // EQFILTERGROUP_H
