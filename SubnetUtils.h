#include"SubnetHelper.h"
//@autor Salvador Vera Franco 
// SubnetUtils.h v 1.0
csubnetutils* utils;

void SubnetUtils(string cidrNotation){
utils=new csubnetutils(cidrNotation);

}

string getWildcard(){
return utils->Info_getWildcard();
}

string getBroadcastAddress(){
return utils->Info_getBroadcastAddress();
}

string getAddress(){
return utils->Info_getAddress();
}

string getNextNetworkAddress(){
return utils->Info_getNextNetworkAddress();
}

string getNetworkAddress(){
return utils->Info_getNetworkAddress();
}

string getDefaultMaskAddress(){
return utils->Info_getDefaultMask();
}

string getNetMaskAddress(){
return utils->Info_getNetmask();
}

string getLowAddress(){
return utils->Info_getLowAddress();
}

string getHighAddress(){
return utils->Info_getHighAddress();
}

long getAddressCount(){
return utils->Info_getAddressCountLong();
}

void setInclusiveHostCount(bool inclusiveHostCount){
    utils->setInclusiveHostCount(inclusiveHostCount);
}

bool isInclusiveHostCount(){
return utils->isInclusiveHostCount();
}
