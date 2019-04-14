/** THIS IS AN AUTOMATICALLY GENERATED FILE.
 *  DO NOT MODIFY BY HAND!!
 *
 *  Generated by zcm-gen
 **/

#include <zcm/zcm_coretypes.h>

#ifndef __groundtruth_imu_t_hpp__
#define __groundtruth_imu_t_hpp__

#include "vector3_t.hpp"
#include "vector3_t.hpp"


/**
 * ZCM type for imu bias ground truth from sim
 *
 */
class groundtruth_imu_t
{
    public:
        int64_t    utime;

        vector3_t  gyro_bias;

        vector3_t  accel_bias;

    public:
        /**
         * Destructs a message properly if anything inherits from it
        */
        virtual ~groundtruth_imu_t() {}

        /**
         * Encode a message into binary form.
         *
         * @param buf The output buffer.
         * @param offset Encoding starts at thie byte offset into @p buf.
         * @param maxlen Maximum number of bytes to write.  This should generally be
         *  equal to getEncodedSize().
         * @return The number of bytes encoded, or <0 on error.
         */
        inline int encode(void* buf, uint32_t offset, uint32_t maxlen) const;

        /**
         * Check how many bytes are required to encode this message.
         */
        inline uint32_t getEncodedSize() const;

        /**
         * Decode a message from binary form into this instance.
         *
         * @param buf The buffer containing the encoded message.
         * @param offset The byte offset into @p buf where the encoded message starts.
         * @param maxlen The maximum number of bytes to reqad while decoding.
         * @return The number of bytes decoded, or <0 if an error occured.
         */
        inline int decode(const void* buf, uint32_t offset, uint32_t maxlen);

        /**
         * Retrieve the 64-bit fingerprint identifying the structure of the message.
         * Note that the fingerprint is the same for all instances of the same
         * message type, and is a fingerprint on the message type definition, not on
         * the message contents.
         */
        inline static int64_t getHash();

        /**
         * Returns "groundtruth_imu_t"
         */
        inline static const char* getTypeName();

        // ZCM support functions. Users should not call these
        inline int      _encodeNoHash(void* buf, uint32_t offset, uint32_t maxlen) const;
        inline uint32_t _getEncodedSizeNoHash() const;
        inline int      _decodeNoHash(const void* buf, uint32_t offset, uint32_t maxlen);
        inline static uint64_t _computeHash(const __zcm_hash_ptr* p);
};

int groundtruth_imu_t::encode(void* buf, uint32_t offset, uint32_t maxlen) const
{
    uint32_t pos = 0;
    int thislen;
    int64_t hash = (int64_t)getHash();

    thislen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if(thislen < 0) return thislen; else pos += thislen;

    thislen = this->_encodeNoHash(buf, offset + pos, maxlen - pos);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int groundtruth_imu_t::decode(const void* buf, uint32_t offset, uint32_t maxlen)
{
    uint32_t pos = 0;
    int thislen;

    int64_t msg_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &msg_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (msg_hash != getHash()) return -1;

    thislen = this->_decodeNoHash(buf, offset + pos, maxlen - pos);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

uint32_t groundtruth_imu_t::getEncodedSize() const
{
    return 8 + _getEncodedSizeNoHash();
}

int64_t groundtruth_imu_t::getHash()
{
    static int64_t hash = _computeHash(NULL);
    return hash;
}

const char* groundtruth_imu_t::getTypeName()
{
    return "groundtruth_imu_t";
}

int groundtruth_imu_t::_encodeNoHash(void* buf, uint32_t offset, uint32_t maxlen) const
{
    uint32_t pos = 0;
    int thislen;

    thislen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &this->utime, 1);
    if(thislen < 0) return thislen; else pos += thislen;

    thislen = this->gyro_bias._encodeNoHash(buf, offset + pos, maxlen - pos);
    if(thislen < 0) return thislen; else pos += thislen;

    thislen = this->accel_bias._encodeNoHash(buf, offset + pos, maxlen - pos);
    if(thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int groundtruth_imu_t::_decodeNoHash(const void* buf, uint32_t offset, uint32_t maxlen)
{
    uint32_t pos = 0;
    int thislen;

    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &this->utime, 1);
    if(thislen < 0) return thislen; else pos += thislen;

    thislen = this->gyro_bias._decodeNoHash(buf, offset + pos, maxlen - pos);
    if(thislen < 0) return thislen; else pos += thislen;

    thislen = this->accel_bias._decodeNoHash(buf, offset + pos, maxlen - pos);
    if(thislen < 0) return thislen; else pos += thislen;

    return pos;
}

uint32_t groundtruth_imu_t::_getEncodedSizeNoHash() const
{
    uint32_t enc_size = 0;
    enc_size += __int64_t_encoded_array_size(NULL, 1);
    enc_size += this->gyro_bias._getEncodedSizeNoHash();
    enc_size += this->accel_bias._getEncodedSizeNoHash();
    return enc_size;
}

uint64_t groundtruth_imu_t::_computeHash(const __zcm_hash_ptr* p)
{
    const __zcm_hash_ptr* fp;
    for(fp = p; fp != NULL; fp = fp->parent)
        if(fp->v == groundtruth_imu_t::getHash)
            return 0;
    const __zcm_hash_ptr cp = { p, (void*)groundtruth_imu_t::getHash };

    uint64_t hash = (uint64_t)0x00ccb14bb473f06dLL +
         vector3_t::_computeHash(&cp) +
         vector3_t::_computeHash(&cp);

    return (hash<<1) + ((hash>>63)&1);
}

#endif
