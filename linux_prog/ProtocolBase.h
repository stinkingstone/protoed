
#include "protoEnDe.h"

class ProtocolBase{
    virtual void encode(Buf4ProtoEncode& cByteBuf)=0;
	virtual void decode(Buf4ProtoDecode& cByteBuf)=0;
};


