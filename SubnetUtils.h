/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


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
