#include <lwcomstreamer.h>
#include <lwcom.h>

static int LwCom::recvMsg(QByteArray &ba, uint32_t size)
{
    //QByteArray preamble1("Msg[");
    //QByteArray preamble2("Msg]");
    int retVal = 0;
   // ulong readBuffer(0);
    ulong leng(0);
    int pre(0);
    do{
        VERIFY(read(),-1);
        //read preamble

        if (    msg->preamble == T_MSG_PREAMBLE
             || msg->preamble == T_MSG_PREAMBLE_RPL )
        {
           preFound = 1;  //preamble int value
           break;
        }
        VERIFY(pre, -2);
        bool header = false;
        for(int i = 0;i<size;i++)
        {
            if(ba[i] == T_MSG_HDR_SZ)
                header = true;
        }
        if(!header)
        {
           break;
        }
        leng = _htons(msg->length);//host to network short
        if(checkCrc(msg) < 0)
            break;

        msg->length = leng;

        retVal = 1;
        }
    while(0);

    return retVal;
}
static void setCrc(T_MSG *msg)
{
    UWORD len;
        if(!msg)
            break;
        len = T_MSG_HDR_WITH_PREAMBLE_SZ + _htons(msg->length);

        msg->crc16 = 0x0000;
        msg->crc16 = _htons(crc_calc(T_MSG_CRC_KEY, &msg->preamble,len));
}

static int LwCom::checkCRC(T_MSG* msg)
{
    int retVal(-1);
    UWORD leng(0), crc16(0), crc16msg(0);

    do
    {
        if(!msg)
            break;
        leng = T_MSG_HDR_WITH_PREAMBLE_SZ + _htons(msg->length);
        if(leng > (T_MSG_HDR_WITH_PREAMBLE_SZ) + T_MAX_MSG_LENGTH)
            break;

        crc16msg = msg->crc16;
        msg->crc16 = 0;
        crc16 = crc_calc(T_MSG_CRC_KEY, msg, leng);
        msg->crc16 = crc16msg;

        if(_htons(msg->crc16) != crc16)
            break;

        retVal = 1;
    }
    while(0);
    return retVal;
}
//first message send: 0xA0, first session id: 0
UWORD LwCom::crc_calc(UWORD crc, PVOID buf, unsigned long nbytes)
{
    unsigned char *p, *lim;

    p = (unsigned char *)buf;
    lim = p + nbytes;

    while(p < lim)
    {
        crc = (crc >> 8) ^ crc_table[(crc & 0xFF) ^ *p++];
    }

    return crc;
}
