#ifndef _CERTIFICATES_H_
#define _CERTIFICATES_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* This file is auto-generated by the pycert_bearssl tool.  Do not change it manually.
 * Certificates are BearSSL br_x509_trust_anchor format.  Included certs:
 *
 * Index:    0
 * Label:    ISRG Root X1
 * Subject:  CN=ISRG Root X1,O=Internet Security Research Group,C=US
 * Domain(s): api.callmebot.com
 * 
 * A simple online generator that you can find here:
 * https://mischianti.org/online-bearssl-certificate-trust-anchor-retriever-for-minimal-x509-verification-engine/
 */

#define TAs_NUM 1

static const unsigned char TA_DN0[] = {
    0x30, 0x4f, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13,
    0x02, 0x55, 0x53, 0x31, 0x29, 0x30, 0x27, 0x06, 0x03, 0x55, 0x04, 0x0a,
    0x13, 0x20, 0x49, 0x6e, 0x74, 0x65, 0x72, 0x6e, 0x65, 0x74, 0x20, 0x53,
    0x65, 0x63, 0x75, 0x72, 0x69, 0x74, 0x79, 0x20, 0x52, 0x65, 0x73, 0x65,
    0x61, 0x72, 0x63, 0x68, 0x20, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x31, 0x15,
    0x30, 0x13, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x0c, 0x49, 0x53, 0x52,
    0x47, 0x20, 0x52, 0x6f, 0x6f, 0x74, 0x20, 0x58, 0x31,
};

static const unsigned char TA_RSA_N0[] = {
    0xad, 0xe8, 0x24, 0x73, 0xf4, 0x14, 0x37, 0xf3, 0x9b, 0x9e, 0x2b, 0x57,
    0x28, 0x1c, 0x87, 0xbe, 0xdc, 0xb7, 0xdf, 0x38, 0x90, 0x8c, 0x6e, 0x3c,
    0xe6, 0x57, 0xa0, 0x78, 0xf7, 0x75, 0xc2, 0xa2, 0xfe, 0xf5, 0x6a, 0x6e,
    0xf6, 0x00, 0x4f, 0x28, 0xdb, 0xde, 0x68, 0x86, 0x6c, 0x44, 0x93, 0xb6,
    0xb1, 0x63, 0xfd, 0x14, 0x12, 0x6b, 0xbf, 0x1f, 0xd2, 0xea, 0x31, 0x9b,
    0x21, 0x7e, 0xd1, 0x33, 0x3c, 0xba, 0x48, 0xf5, 0xdd, 0x79, 0xdf, 0xb3,
    0xb8, 0xff, 0x12, 0xf1, 0x21, 0x9a, 0x4b, 0xc1, 0x8a, 0x86, 0x71, 0x69,
    0x4a, 0x66, 0x66, 0x6c, 0x8f, 0x7e, 0x3c, 0x70, 0xbf, 0xad, 0x29, 0x22,
    0x06, 0xf3, 0xe4, 0xc0, 0xe6, 0x80, 0xae, 0xe2, 0x4b, 0x8f, 0xb7, 0x99,
    0x7e, 0x94, 0x03, 0x9f, 0xd3, 0x47, 0x97, 0x7c, 0x99, 0x48, 0x23, 0x53,
    0xe8, 0x38, 0xae, 0x4f, 0x0a, 0x6f, 0x83, 0x2e, 0xd1, 0x49, 0x57, 0x8c,
    0x80, 0x74, 0xb6, 0xda, 0x2f, 0xd0, 0x38, 0x8d, 0x7b, 0x03, 0x70, 0x21,
    0x1b, 0x75, 0xf2, 0x30, 0x3c, 0xfa, 0x8f, 0xae, 0xdd, 0xda, 0x63, 0xab,
    0xeb, 0x16, 0x4f, 0xc2, 0x8e, 0x11, 0x4b, 0x7e, 0xcf, 0x0b, 0xe8, 0xff,
    0xb5, 0x77, 0x2e, 0xf4, 0xb2, 0x7b, 0x4a, 0xe0, 0x4c, 0x12, 0x25, 0x0c,
    0x70, 0x8d, 0x03, 0x29, 0xa0, 0xe1, 0x53, 0x24, 0xec, 0x13, 0xd9, 0xee,
    0x19, 0xbf, 0x10, 0xb3, 0x4a, 0x8c, 0x3f, 0x89, 0xa3, 0x61, 0x51, 0xde,
    0xac, 0x87, 0x07, 0x94, 0xf4, 0x63, 0x71, 0xec, 0x2e, 0xe2, 0x6f, 0x5b,
    0x98, 0x81, 0xe1, 0x89, 0x5c, 0x34, 0x79, 0x6c, 0x76, 0xef, 0x3b, 0x90,
    0x62, 0x79, 0xe6, 0xdb, 0xa4, 0x9a, 0x2f, 0x26, 0xc5, 0xd0, 0x10, 0xe1,
    0x0e, 0xde, 0xd9, 0x10, 0x8e, 0x16, 0xfb, 0xb7, 0xf7, 0xa8, 0xf7, 0xc7,
    0xe5, 0x02, 0x07, 0x98, 0x8f, 0x36, 0x08, 0x95, 0xe7, 0xe2, 0x37, 0x96,
    0x0d, 0x36, 0x75, 0x9e, 0xfb, 0x0e, 0x72, 0xb1, 0x1d, 0x9b, 0xbc, 0x03,
    0xf9, 0x49, 0x05, 0xd8, 0x81, 0xdd, 0x05, 0xb4, 0x2a, 0xd6, 0x41, 0xe9,
    0xac, 0x01, 0x76, 0x95, 0x0a, 0x0f, 0xd8, 0xdf, 0xd5, 0xbd, 0x12, 0x1f,
    0x35, 0x2f, 0x28, 0x17, 0x6c, 0xd2, 0x98, 0xc1, 0xa8, 0x09, 0x64, 0x77,
    0x6e, 0x47, 0x37, 0xba, 0xce, 0xac, 0x59, 0x5e, 0x68, 0x9d, 0x7f, 0x72,
    0xd6, 0x89, 0xc5, 0x06, 0x41, 0x29, 0x3e, 0x59, 0x3e, 0xdd, 0x26, 0xf5,
    0x24, 0xc9, 0x11, 0xa7, 0x5a, 0xa3, 0x4c, 0x40, 0x1f, 0x46, 0xa1, 0x99,
    0xb5, 0xa7, 0x3a, 0x51, 0x6e, 0x86, 0x3b, 0x9e, 0x7d, 0x72, 0xa7, 0x12,
    0x05, 0x78, 0x59, 0xed, 0x3e, 0x51, 0x78, 0x15, 0x0b, 0x03, 0x8f, 0x8d,
    0xd0, 0x2f, 0x05, 0xb2, 0x3e, 0x7b, 0x4a, 0x1c, 0x4b, 0x73, 0x05, 0x12,
    0xfc, 0xc6, 0xea, 0xe0, 0x50, 0x13, 0x7c, 0x43, 0x93, 0x74, 0xb3, 0xca,
    0x74, 0xe7, 0x8e, 0x1f, 0x01, 0x08, 0xd0, 0x30, 0xd4, 0x5b, 0x71, 0x36,
    0xb4, 0x07, 0xba, 0xc1, 0x30, 0x30, 0x5c, 0x48, 0xb7, 0x82, 0x3b, 0x98,
    0xa6, 0x7d, 0x60, 0x8a, 0xa2, 0xa3, 0x29, 0x82, 0xcc, 0xba, 0xbd, 0x83,
    0x04, 0x1b, 0xa2, 0x83, 0x03, 0x41, 0xa1, 0xd6, 0x05, 0xf1, 0x1b, 0xc2,
    0xb6, 0xf0, 0xa8, 0x7c, 0x86, 0x3b, 0x46, 0xa8, 0x48, 0x2a, 0x88, 0xdc,
    0x76, 0x9a, 0x76, 0xbf, 0x1f, 0x6a, 0xa5, 0x3d, 0x19, 0x8f, 0xeb, 0x38,
    0xf3, 0x64, 0xde, 0xc8, 0x2b, 0x0d, 0x0a, 0x28, 0xff, 0xf7, 0xdb, 0xe2,
    0x15, 0x42, 0xd4, 0x22, 0xd0, 0x27, 0x5d, 0xe1, 0x79, 0xfe, 0x18, 0xe7,
    0x70, 0x88, 0xad, 0x4e, 0xe6, 0xd9, 0x8b, 0x3a, 0xc6, 0xdd, 0x27, 0x51,
    0x6e, 0xff, 0xbc, 0x64, 0xf5, 0x33, 0x43, 0x4f,
};

static const unsigned char TA_RSA_E0[] = {
    0x01, 0x00, 0x01,
};

static const br_x509_trust_anchor TAs[] = {
    {
        { (unsigned char *)TA_DN0, sizeof TA_DN0 },
        BR_X509_TA_CA,
        {
            BR_KEYTYPE_RSA,
            { .rsa = {
                (unsigned char *)TA_RSA_N0, sizeof TA_RSA_N0,
                (unsigned char *)TA_RSA_E0, sizeof TA_RSA_E0,
            } }
        }
    },
};

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ifndef _CERTIFICATES_H_ */
