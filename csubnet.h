
//@autor Salvador Vera Franco 
// csubnet.h v 1.0


#include <string>
#include <regex>
#include <math.h>
#include <limits>
#include <bitset>
#include <algorithm>
#include<climits>
#include <exception>
#include <stdexcept>
using namespace std;
#define IP_ADDRESS_FORMAT "(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})"
#define SLASH_FORMAT "/(\\d{1,2})"

class csubnethelper{
	protected:

            static int rangeCheck(int value, int begin, int end) {
                if (value >= begin && value <= end) {
                    return value;
                    }
                throw  out_of_range("Value ["+to_string( value)+" ] not in range ["+to_string(begin)+","+to_string(end)+"])");
            }


            static int matchAddress(string ip) {

                string slashformat=SLASH_FORMAT;
                string ipaddrssformat=IP_ADDRESS_FORMAT;
                regex addressPattern(ipaddrssformat+slashformat);

                smatch  match;
                regex_match(ip,match,addressPattern);

                int addr = 0;
                int oct;

                for (int i = 1; i <= 4; ++i) {
                    oct=stoi(match[i]);

                    int n = (rangeCheck(oct, 0, 255));
                    addr |= ((n & 0xff) << 8*(4-i));
                }
            return addr;
            }

            string format_toArray(int val) {
                int arr[4];
                unsigned int value=val;
                for (int j = 0; j <4; ++j) {
                 // arr[j]=((value >> 8*(3-j)) && (0xff));
                    value=val>> 8*(3-j);
                    arr[j]=((value & 0xff));
                }

                string str;

                for (int i =0; i < 4; ++i){
                    str.append(to_string(arr[i]));
                    if (i != (4)-1 ) {
                        str.append(".");
                    }
                }
            return str;
            }

	private:
            long getTotalHost(long HOST,bool ADD_ID_AND_BROADCAST,bool return_exponent){
                long totalhost=0;
                long b=0;
                long HOST_2=HOST+(ADD_ID_AND_BROADCAST ? 2 : 0);
                int exponent=1;

                while((b != HOST_2)){
                    if(exponent<33){
                        totalhost=(long)pow(2,exponent)*((HOST_2 <= 256) ? 1 : 256);
                        b=min(HOST_2, totalhost);
                        exponent++;
                    }
                    else break;
                }
            return (return_exponent ? (HOST_2 <= 256 ? exponent-1 : exponent+7) :totalhost);
            }


            static int getUsedMaskBits(int NET_ADDRESS_1,int NET_ADDRESS_2){
                bitset< 8 > net1 (NET_ADDRESS_1);
                bitset< 8 > net2 (NET_ADDRESS_2);
                string netbits1=net1.to_string();
                string netbits2=net2.to_string();
                int bits=0;
                if(netbits1.length()==netbits2.length()){
                    for(unsigned int x=0;x<netbits1.length();x++){
                        if(netbits1.substr(0,x)==netbits2.substr(0,x))
                            bits= x+(32-netbits1.length());
                        else break;

                    }

                }
                else throw invalid_argument("Network Address NO Match\n") ;

            return bits;
            }
	public:


   /**
     * @brief Returns the TOTALHOST to NHOST
     * @param NHOST Can be any number less than 2^32
     * @param ADD_ID_AND_BROADCAST if it's true sum 2 at NHOST
     * @return TOTALHOST or zero if HOST is wrong
     */
            long get_Total_Host(long NHOST,bool ADD_ID_AND_BROADCAST){
                long totalhost=0;
                long b=0;
                long HOST_2=NHOST+(ADD_ID_AND_BROADCAST ? 2 : 0);
                int exponent=1;
                if(HOST_2<=pow(2,32)&&HOST_2>0){
                    while((b != HOST_2)){
                        if(exponent<33){
                            totalhost=(long)pow(2,exponent)*((HOST_2 <= 256) ? 1 : 256);
                            b=min(HOST_2,totalhost );
                            exponent++;
                        }
                        else break;
                    }
                }
            return totalhost;
            }

    /**
     * @brief Return Default mask.
     * @param ipaddress An IP address, e.g. "192.168.0.1"
     * @return  Default mask or "Not defined"
     */

            string DefaultMask(string ipaddress){
                string defmask="";
                int first=stoi(ipaddress.substr(ipaddress.find(""),ipaddress.find(".")));
                if(first>=0&&first<128)
                    defmask="255.0.0.0";
                else if(first>127&&first<192)
                    defmask="255.255.0.0";
                else if(first>191&&first<224)
                    defmask="255.255.255.0";
                else
                    defmask="Not defined";
            return defmask;
            }


            static const int MASK_ADDRESS=1;
            static const int SLASH_FORMAT_MASK=-1;

                 /**
     * Returns the NETMASK
     * @param NHOST Can be any number less than 2^32
     * @param FORMAT Use variable SLASH_FORMAT_MASK or MASK_ADDRESS
     * @return TOTALHOST or zero if HOST is wrong
     * @throw invalid_argument if the FORMAT is invalid, or NHOST is out range
     */
            string getNetMask(long NHOST,const int FORMAT){
                string RETURN="";
                string mask;
                int trailingZero;
                if(NHOST>0&&NHOST<=pow(2, 32)){

                    mask=to_string(32-getTotalHost(NHOST, false, true));

                    switch(FORMAT){
                        case SLASH_FORMAT_MASK:
                                RETURN= "/"+mask;
                                break;

                        case MASK_ADDRESS:
                            trailingZero = (32 - rangeCheck(stoi(mask), 0, 32));
                            RETURN=format_toArray((int) (0x0FFFFFFFFL << trailingZero ));
                            break;

                        default: throw invalid_argument("Incorrect Format"); break;
                    }
                }else throw  invalid_argument("");

            return RETURN;
            }

          //  string Summarize(string*);


};

/* ***********************************************************************************
 *  csubnetutils class                                                               *
 *************************************************************************************/


   class csubnetutils:public csubnethelper{
    private:
      // static const int NBITS=32;
        int netmask;
        int address;
        int network;
        int broadcast;
       bool inclusiveHostCount = false;
        /* Mask to convert unsigned int to a long (i.e. keep 32 bits) */
        static const long UNSIGNED_INT_MASK = 0x0FFFFFFFFL;

        // long versions of the values (as unsigned int) which are more suitable for range checking
        long networkLong()  { return network &  UNSIGNED_INT_MASK; }
        long broadcastLong(){ return broadcast &  UNSIGNED_INT_MASK; }

        int low() {
            return (isInclusiveHostCount() ? network :
                broadcastLong() - networkLong() > 1 ? network + 1 : 0);
        }

        int high() {
            return (isInclusiveHostCount() ? broadcast :
                broadcastLong() - networkLong() > 1 ? broadcast -1  : 0);
        }


    public:

       csubnetutils(string cidrNotation){
            string slashformat=SLASH_FORMAT;
            string ipaddrssformat=IP_ADDRESS_FORMAT;
            regex match(ipaddrssformat+slashformat);
            smatch cidrmatch;
                regex_match(cidrNotation,cidrmatch,match);

                string net=cidrNotation;
            if(regex_match(cidrNotation,match)){

               this->address=matchAddress(cidrNotation);

               int trailingZeroes = 32 - rangeCheck(stoi(cidrmatch[5]), 0, 32);

               this->netmask = (int) (0x0FFFFFFFFL << trailingZeroes );

               this->network = (address & netmask);

               this->broadcast = network | ~(netmask);

                }
                else {
                throw invalid_argument("Could not parse [" + cidrNotation + "]");
                }

        }
        ~csubnetutils(){}

    /**
     * Returns <code>true</code> if the return value of {@link SubnetInfo#getAddressCount()}
     * includes the network and broadcast addresses.
     *
     * @return true if the host count includes the network and broadcast addresses
     */
        bool isInclusiveHostCount() {
            return inclusiveHostCount;
        }
    /**
     * Set to <code>true</code> if you want the return value of {@link SubnetInfo#getAddressCount()}
     * to include the network and broadcast addresses.
     * @param inclusiveHostCount true if network and broadcast addresses are to be included
     *
     */
        void setInclusiveHostCount(bool inclusiveHostCount) {
        this->inclusiveHostCount = inclusiveHostCount;
        }



        string Info_getBroadcastAddress() {
            return format_toArray(broadcast);
        }


        string Info_getNextNetworkAddress() {
            return format_toArray(broadcast+1);
        }

        string Info_getNetworkAddress() {
            return format_toArray(network);
        }


        string Info_getDefaultMask(){
        return DefaultMask(Info_getNetworkAddress());
        }


        string Info_getNetmask() {
            return format_toArray(netmask);
        }


        string Info_getWildcard() {
            return format_toArray((-1)-netmask);
        }


        string Info_getAddress() {
            return format_toArray(address);
        }

        /**
         * Return the low address as a dotted IP address.
         * Will be zero for CIDR/31 and CIDR/32 if the inclusive flag is false.
         *
         * @return the IP address in dotted format, may be "0.0.0.0" if there is no valid address
         */
        string Info_getLowAddress() {
            return format_toArray(low());
        }

        /**
         * Return the high address as a dotted IP address.
         * Will be zero for CIDR/31 and CIDR/32 if the inclusive flag is false.
         *
         * @return the IP address in dotted format, may be "0.0.0.0" if there is no valid address
         */
        string Info_getHighAddress() {
            return format_toArray(high());
        }

        /**
         * Get the count of available addresses.
         * Will be zero for CIDR/31 and CIDR/32 if the inclusive flag is false.
         * @return the count of addresses, may be zero.
         *
         */
        long Info_getAddressCountLong() {
            long b = broadcastLong();
            long n = networkLong();
            long count = b - n + (isInclusiveHostCount() ? 1 : -1);
            return count < 0 ? 0 : count;
        }



   };
