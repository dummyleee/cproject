#include <iostream>
#include<ctime>
#include<math.h>
#include<time.h>
# define F(x,y,z) ((x&y)|((~x)&z))
# define G(x,y,z) ((x&y)|(x&z)|(y&z))
# define H(x,y,z) (x^y^z)
# define LROT(x,s)  (((x)<<s)|((x)>>(32-s)))
# define RROT(x,s)  (((x)>>s)|((x)<<(32-s)))
# define bit(x,n)   ((x<<(32-n))>>31)

using namespace std;


unsigned long result[4];
unsigned long ulrand(){

    return(
           (((unsigned long)rand()<<24)&0xFF000000ul)|
           (((unsigned long)rand()<<12)&0x00FFF000ul)|
           (((unsigned long)rand())&0x00000FFFul));
}
unsigned long generateRand(){

    return ulrand();
}
 void MD4(unsigned long M[]){
    unsigned long a[13], b[13], c[13], d[13];
	//unsigned long a1[13], b1[13], c1[13], d1[13];
	unsigned long k1, k2;
    a[0] = 0x67452301;
	b[0] = 0xefcdab89;
	c[0] = 0x98badcfe;
	d[0] = 0x10325476;
    k1 = 0x5a827999;
	k2 = 0x6ed9eba1;
    a[1] = LROT((a[0] + F(b[0], c[0], d[0]) + M[0]), 3);
	d[1] = LROT((d[0] + F(a[1], b[0], c[0]) + M[1]), 7);
	c[1] = LROT((c[0] + F(d[1], a[1], b[0]) + M[2]), 11);
	b[1] = LROT((b[0] + F(c[1], d[1], a[1]) + M[3]), 19);


	a[2] = LROT((a[1] + F(b[1], c[1], d[1]) + M[4]), 3);
	d[2] = LROT((d[1] + F(a[2], b[1], c[1]) + M[5]), 7);
	c[2] = LROT((c[1] + F(d[2], a[2], b[1]) + M[6]), 11);
	b[2] = LROT((b[1] + F(c[2], d[2], a[2]) + M[7]), 19);


	a[3] = LROT((a[2] + F(b[2], c[2], d[2]) + M[8]), 3);
	d[3] = LROT((d[2] + F(a[3], b[2], c[2]) + M[9]), 7);
	c[3] = LROT((c[2] + F(d[3], a[3], b[2]) + M[10]), 11);
	b[3] = LROT((b[2] + F(c[3], d[3], a[3]) + M[11]), 19);


	a[4] = LROT((a[3] + F(b[3], c[3], d[3]) + M[12]), 3);
	d[4] = LROT((d[3] + F(a[4], b[3], c[3]) + M[13]), 7);
	c[4] = LROT((c[3] + F(d[4], a[4], b[3]) + M[14]), 11);
	b[4] = LROT((b[3] + F(c[4], d[4], a[4]) + M[15]), 19);


	a[5] = LROT((a[4] + G(b[4], c[4], d[4]) + M[0] + k1), 3);
	d[5] = LROT((d[4] + G(a[5], b[4], c[4]) + M[4] + k1), 5);
	c[5] = LROT((c[4] + G(d[5], a[5], b[4]) + M[8] + k1), 9);
	b[5] = LROT((b[4] + G(c[5], d[5], a[5]) + M[12] + k1), 13);


	a[6] = LROT((a[5] + G(b[5], c[5], d[5]) + M[1] + k1), 3);
	d[6] = LROT((d[5] + G(a[6], b[5], c[5]) + M[5] + k1), 5);
	c[6] = LROT((c[5] + G(d[6], a[6], b[5]) + M[9] + k1), 9);
	b[6] = LROT((b[5] + G(c[6], d[6], a[6]) + M[13] + k1), 13);

	a[7] = LROT((a[6] + G(b[6], c[6], d[6]) + M[2] + k1), 3);
	d[7] = LROT((d[6] + G(a[7], b[6], c[6]) + M[6] + k1), 5);
	c[7] = LROT((c[6] + G(d[7], a[7], b[6]) + M[10] + k1), 9);
	b[7] = LROT((b[6] + G(c[7], d[7], a[7]) + M[14] + k1), 13);

	a[8] = LROT((a[7] + G(b[7], c[7], d[7]) + M[3] + k1), 3);
	d[8] = LROT((d[7] + G(a[8], b[7], c[7]) + M[7] + k1), 5);
	c[8] = LROT((c[7] + G(d[8], a[8], b[7]) + M[11] + k1), 9);
	b[8] = LROT((b[7] + G(c[8], d[8], a[8]) + M[15] + k1), 13);

	a[9] = LROT((a[8] + H(b[8], c[8], d[8]) + M[0] + k2), 3);
	d[9] = LROT((d[8] + H(a[9], b[8], c[8]) + M[8] + k2), 9);
	c[9] = LROT((c[8] + H(d[9], a[9], b[8]) + M[4] + k2), 11);
	b[9] = LROT((b[8] + H(c[9], d[9], a[9]) + M[12] + k2), 15);

	a[10] = LROT((a[9] + H(b[9], c[9], d[9]) + M[2] + k2), 3);
	d[10] = LROT((d[9] + H(a[10], b[9], c[9]) + M[10] + k2), 9);
	c[10] = LROT((c[9] + H(d[10], a[10], b[9]) + M[6] + k2), 11);
	b[10] = LROT((b[9] + H(c[10], d[10], a[10]) + M[14] + k2), 15);

	a[11] = LROT((a[10] + H(b[10], c[10], d[10]) + M[1] + k2), 3);
	d[11] = LROT((d[10] + H(a[11], b[10], c[10]) + M[9] + k2), 9);
	c[11] = LROT((c[10] + H(d[11], a[11], b[10]) + M[5] + k2), 11);
	b[11] = LROT((b[10] + H(c[11], d[11], a[11]) + M[13] + k2), 15);

	a[12] = LROT((a[11] + H(b[11], c[11], d[11]) + M[3] + k2), 3);
	d[12] = LROT((d[11] + H(a[12], b[11], c[11]) + M[11] + k2), 9);
	c[12] = LROT((c[11] + H(d[12], a[12], b[11]) + M[7] + k2), 11);
	b[12] = LROT((b[11] + H(c[12], d[12], a[12]) + M[15] + k2), 15);

    result[0] = a[12];
    result[1] = d[12];
    result[2] = c[12];
    result[3] = b[12];
    /*
    cout<<hex<<"1:"<<a[1]<<endl;
	cout<<hex<<"2:"<<d[1]<<endl;
	cout<<hex<<"3:"<<c[1]<<endl;
	cout<<hex<<"4:"<<b[1]<<endl;
    cout<<hex<<"5:"<<a[2]<<endl;
	cout<<hex<<"6:"<<d[2]<<endl;
	cout<<hex<<"7:"<<c[2]<<endl;
	cout<<hex<<"8:"<<b[2]<<endl;
    cout<<hex<<"9:"<<a[3]<<endl;
	cout<<hex<<"10:"<<d[3]<<endl;
	cout<<hex<<"11:"<<c[3]<<endl;
	cout<<hex<<"12:"<<b[3]<<endl;
    cout<<hex<<"13:"<<a[4]<<endl;
	cout<<hex<<"14:"<<d[4]<<endl;
	cout<<hex<<"15:"<<c[4]<<endl;
	cout<<hex<<"16:"<<b[4]<<endl;
    */

 }
int main()
{
    /*
    for(int i=0;i<16;i++){
        cout<<hex<<x[i]<<endl;
    }
    */
    unsigned long M[16];
    unsigned long M1[16];
    unsigned long a[13], b[13], c[13], d[13];
	//unsigned long a1[13], b1[13], c1[13], d1[13];
    a[0] = 0x67452301;
	b[0] = 0xefcdab89;
	c[0] = 0x98badcfe;
	d[0] = 0x10325476;
	int flag = 0;
	while(!flag){
    clock_t startTime,endTime;
    startTime = clock();
    endTime = clock();
    unsigned int t =(unsigned)time(NULL);
    srand(t);
    cout<<t<<endl;
	while( double((endTime - startTime)/CLOCKS_PER_SEC)<20&&(!flag)){
    flag = 1;

    M[0] = generateRand();
    a[1] = LROT((a[0] + F(b[0], c[0], d[0]) + M[0]), 3);
    //cout<<hex<<a[1]<<endl;
    a[1] = a[1]^ ((bit(a[1],7)^bit(b[0],7))<<6);
   // cout<<hex<<a[1]<<endl;
    M[0] = RROT(a[1],3)-a[0]-F(b[0],c[0],d[0]);

    M[1] = generateRand();
    d[1] = LROT((d[0] + F(a[1], b[0], c[0]) + M[1]), 7);
    //cout<<hex<<d[1]<<endl;
    d[1] = d[1]^ (bit(d[1],7)<<6)
               ^ ((bit(d[1],8)^bit(a[1],8))<<7)
               ^ ((bit(d[1],11)^bit(a[1],11))<<10);
    //cout<<hex<<d[1]<<endl;
    M[1] = RROT(d[1],7)-d[0] - F(a[1],b[0],c[0]);
    //cout<<hex<<M[1]<<endl;

    M[2] = generateRand();
    c[1] = LROT((c[0] + F(d[1], a[1], b[0]) + M[2]), 11);
    c[1] = c[1]^ (bit(~c[1],7)<<6)
               ^ (bit(~c[1],8)<<7)
               ^ (bit(c[1],11)<<10)
               ^ ((bit(c[1],26)^bit(d[1],26))<<25);

    M[2] = RROT(c[1], 11)-c[0]-F(d[1],a[1],b[0]);

    M[3] = generateRand();
    b[1] = LROT((b[0] + F(c[1], d[1], a[1]) + M[3]), 19);
    b[1] = b[1]^ (bit(~b[1],7)<<6)
               ^ (bit(b[1],8)<<7)
               ^ (bit(b[1],11)<<10)
               ^ (bit(b[1],26)<<25);
    M[3] = RROT(b[1], 19)-b[0]-F(c[1],d[1],a[1]);

    M[4] = generateRand();
    a[2] = LROT((a[1] + F(b[1], c[1], d[1]) + M[4]),3);
    a[2] = a[2]^ (bit(~a[2],8)<<7)
               ^ (bit(~a[2],11)<<10)
               ^ (bit(a[2], 26)<<25)
               ^ ((bit(a[2],14)^bit(b[1],14))<<13);
    M[4] = RROT(a[2], 3)-a[1]-F(b[1],c[1],d[1]);

    M[5] = generateRand();
    d[2] = LROT((d[1] + F(a[2], b[1], c[1]) + M[5]), 7);
    d[2] = d[2]^ (bit(d[2], 14)<<13)
               ^ ((bit(d[2], 19)^bit(a[2], 19))<<18)
               ^ ((bit(d[2], 20)^bit(a[2], 20))<<19)
               ^ ((bit(d[2], 21)^bit(a[2], 21))<<20)
               ^ ((bit(d[2], 22)^bit(a[2], 22))<<21)
               ^ (bit(~d[2], 26)<<25);
    M[5] = RROT(d[2], 7)- d[1] - F(a[2], b[1], c[1]);

    M[6] = generateRand();
    c[2] = LROT((c[1] + F(d[2], a[2], b[1]) + M[6]), 11);
    c[2] = c[2]^ ((bit(c[2], 13)^bit(d[2], 13))<<12)
               ^ (bit(c[2], 14)<<13)
               ^ ((bit(c[2], 15)^bit(d[2], 15))<<14)
               ^ (bit(c[2], 19)<<18)
               ^ (bit(c[2], 20)<<19)
               ^ (bit(~c[2], 21)<<20)
               ^ (bit(c[2], 22)<<21);
    M[6] = RROT(c[2], 11) - c[1] -F(d[2], a[2], b[1]);

    M[7] = generateRand();
    b[2] = LROT((b[1] + F(c[2], d[2], a[2]) + M[7]), 19);
    b[2] = b[2]^ (bit(~b[2], 13)<<12)
               ^ (bit(~b[2], 14)<<13)
               ^ (bit(b[2], 15)<<14)
               ^ ((bit(b[2], 17)^bit(c[2],17))<<16)
               ^ (bit(b[2], 19)<<18)
               ^ (bit(b[2], 20)<<19)
               ^ (bit(b[2], 21)<<20)
               ^ (bit(b[2], 22)<<21);
    M[7] = RROT(b[2], 19) - b[1] - F(c[2], d[2], a[2]);

    M[8] = generateRand();
    a[3] = LROT((a[2] + F(b[2], c[2], d[2]) + M[8]), 3);
    a[3] = a[3]^ (bit(~a[3], 13)<<12)
               ^ (bit(~a[3], 14)<<13)
               ^ (bit(~a[3], 15)<<14)
               ^ (bit(a[3], 17)<<16)
               ^ (bit(a[3], 19)<<18)
               ^ (bit(a[3], 20)<<19)
               ^ (bit(a[3], 21)<<20)
               ^ ((bit(a[3], 23)^bit(b[2], 23))<<22)
               ^ (bit(~a[3], 22)<<21)
               ^ ((bit(a[3], 26)^bit(b[2], 26))<<25);
    M[8] = RROT(a[3], 3) - a[2] -F(b[2], c[2], d[2]);

    M[9] = generateRand();
    d[3] = LROT((d[2] + F(a[3], b[2], c[2]) + M[9]), 7);
    d[3] = d[3]^ (bit(~d[3], 13)<<12)
               ^ (bit(~d[3], 14)<<13)
               ^ (bit(~d[3], 15)<<14)
               ^ (bit(d[3], 17)<<16)
               ^ (bit(d[3], 20)<<19)
               ^ (bit(~d[3], 21)<<20)
               ^ (bit(~d[3], 22)<<21)
               ^ (bit(d[3], 23)<<22)
               ^ (bit(~d[3], 26)<<25)
               ^ ((bit(d[3], 30)^bit(a[3], 30))<<29);
    M[9] = RROT(d[3], 7) - d[2] -F(a[3], b[2], c[2]);

    M[10] = generateRand();
    c[3] = LROT((c[2] + F(d[3], a[3], b[2]) + M[10]), 11);
    c[3] = c[3]^ (bit(~c[3], 17)<<16)
               ^ (bit(c[3], 20)<<19)
               ^ (bit(c[3], 21)<<20)
               ^ (bit(c[3], 22)<<21)
               ^ (bit(c[3], 23)<<22)
               ^ (bit(c[3], 26)<<25)
               ^ (bit(~c[3], 30)<<29)
               ^ ((bit(c[3], 32)^bit(d[3], 32))<<31);
 //              ^ ((bit(c[3], 1)^bit(d[3], 1)));
    M[10] = RROT(c[3], 11) - c[2] - F(d[3], a[3], b[2]);

    M[11] = generateRand();
    b[3] = LROT((b[2] + F(c[3], d[3], a[3]) + M[11]), 19);
    b[3] = b[3]^ (bit(b[3], 20)<<19)
               ^ (bit(~b[3], 21)<<20)
               ^ (bit(~b[3], 22)<<21)
               ^ ((bit(b[3], 23)^bit(c[3], 23))<<22)
               ^ (bit(~b[3], 26)<<25)
               ^ (bit(b[3], 30)<<29)
               ^ (bit(b[3], 32)<<31);
  //             ^ (bit(b[3], 1));
    M[11] = RROT(b[3], 19) - b[2] - F(c[3], d[3], a[3]);

    M[12] = generateRand();
    a[4] = LROT((a[3] + F(b[3], c[3], d[3]) + M[12]), 3);
    a[4] = a[4]^ (bit(a[4], 23)<<22)
               ^ (bit(a[4], 26)<<25)
               ^ ((bit(a[4], 27)^bit(b[3], 27))<<26)
               ^ ((bit(a[4], 29)^bit(b[3], 29))<<28)
               ^ (bit(~a[4], 30)<<29)
               ^ (bit(a[4], 32)<<31);
   //            ^ (bit(a[4], 1));
    M[12] = RROT(a[4], 3) - a[3] - F(b[3], c[3], d[3]);

    M[13] = generateRand();
    d[4] = LROT((d[3] + F(a[4], b[3], c[3]) + M[13]), 7);
    d[4] = d[4]^ (bit(d[4], 23)<<22)
               ^ (bit(d[4], 26)<<25)
               ^ (bit(~d[4], 27)<<26)
               ^ (bit(~d[4], 29)<<28)
               ^ (bit(d[4], 30)<<29)
               ^ (bit(~d[4], 32)<<31);
 //              ^ (bit(~d[4], 1));
    M[13] = RROT(d[4], 7) - d[3] - F(a[4], b[3], c[3]);

    M[14] = generateRand();
    c[4] = LROT((c[3] + F(d[4], a[4], b[3]) + M[14]), 11);
    c[4] = c[4]^ ((bit(c[4], 19)^bit(d[4], 19))<<18)
               ^ (bit(~c[4], 23)<<22)
               ^ (bit(~c[4], 26)<<25)
               ^ (bit(c[4], 27)<<26)
               ^ (bit(c[4], 29)<<28)
               ^ (bit(c[4], 30)<<29);
    M[14] = RROT(c[4], 11) - c[3] - F(d[4], a[4], b[3]);

    M[15] = generateRand();
    b[4] = LROT((b[3] + F(c[4], d[4], a[4]) + M[15]), 19);
    b[4] = b[4]^ (bit(b[4], 19)<<18)
               ^ (bit(~b[4], 26)<<25)
               ^ (bit(~b[4], 27)<<26)
               ^ (bit(~b[4], 29)<<28)
               ^ (bit(b[4], 30)<<29);
    M[15] = RROT(b[4], 19) - b[3] - F(c[4], d[4], a[4]);
    for(int i=0;i<16;i++)
    {
        M1[i] = M[i];
    }
    M1[1] = M[1]+0x80000000;
    M1[2] = M[2]+0x70000000;
    M1[12] =M[12]-0x10000;
    unsigned long M_R[4];
    MD4(M);
    for(int i=0;i<4;i++)
        M_R[i] = result[i];
    MD4(M1);
    for(int i=0;i<4;i++)
    {
        if(M_R[i] != result[i])
        {
            flag = 0;
            break;
        }
    }
    endTime = clock();
	}
	cout<<"1"<<endl;
	}
   // cout<<hex<<~bit(x[1],1)<<endl;
   // cout<<hex<<LROT((a[0] + F(b[0], c[0], d[0]) + M[0]), 3)<<endl;
    //unsigned long n1 =0x80000000;
    //unsigned long n2 =0x80000000;
    //cout<<hex<<n1+n2<<endl;
    for(int i=0;i<16;i++){
        cout<<hex<<M[i]<<"  ";
    }
    cout<<endl;
    MD4(M);
    for(int i=0;i<4;i++)
        cout<<hex<<result[i]<<"  ";
    cout<<endl;
     for(int i=0;i<16;i++){
        cout<<hex<<M1[i]<<"  ";
    }
    cout<<endl;
    MD4(M1);
    for(int i=0;i<4;i++)
        cout<<hex<<result[i]<<"  ";
    cout<<endl;
    return 0;
}
    /*
    //µÚ¶þÂÖ
    a[5] = LROT((a[4] + G(b[4], c[4], d[4]) + M[0] + k1), 3);
    if ((bit(a[5],19) ^ bit(c[4], 19))
        || (!bit(a[5], 26))
        || (bit(a[5], 27))
        || (!bit(a[5], 29))
        || (!bit(a[5], 32)))
    {
        flag = 0;
        continue;
    }
    d[5] = LROT((d[4] + G(a[5], b[4], c[4]) + M[4] + k1), 5);
    if((bit(d[5], 19)^bit(a[5], 19))
       ||(bit(d[5], 26)^bit(b[4], 26))
       ||(bit(d[5], 27)^bit(b[4], 27))
       ||(bit(d[5], 29)^bit(b[4], 29))
       ||(bit(d[5], 32)^bit(b[4], 32)))
    {
        flag = 0;
        continue;
    }
    c[5] = LROT((c[4] + G(d[5], a[5], b[4]) + M[8] + k1), 9);
    if((bit(c[5], 26)^bit(d[5], 26))
       ||(bit(c[5], 27)^bit(d[5], 27))
       ||(bit(c[5], 29)^bit(d[5], 29))
       ||(bit(c[5], 30)^bit(d[5], 30))
       ||(bit(c[5], 32)^bit(d[5], 32)))
    {
      flag = 0;
      continue;

    }
    b[5] = LROT((b[4] + G(c[5], d[5], a[5]) + M[12] + k1), 13);
    if((bit(b[5], 29)^bit(c[5], 29))
       ||(!bit(b[5], 30))
       ||(bit(b[5], 32)))
    {
        flag =0;
        continue;
    }
    a[6] = LROT((a[5] + G(b[5], c[5], d[5]) + M[1] + k1), 3);
    if((!bit(a[6], 29))
       ||(!bit(a[6], 32)))
    {
        flag =0;
        continue;
    }
    d[6] = LROT((d[5] + G(a[6], b[5], c[5]) + M[5] + k1), 5);
    if((bit(d[6], 29)^bit(b[5], 29)))
	{
	    flag = 0;
	    continue;
	}
	c[6] = LROT((c[5] + G(d[6], a[6], b[5]) + M[9] + k1), 9);
	if((bit(c[6], 29)^bit(d[6], 29))
       ||(bit(c[6], 30)^(!bit(d[6], 30)))
       ||(bit(c[6], 32)^(!bit(d[6], 32))))
    {
        flag = 0;
        continue;
    }
    b[6] = LROT((b[5] + G(c[6], d[6], a[6]) + M[13] + k1), 13);

	a[7] = LROT((a[6] + G(b[6], c[6], d[6]) + M[2] + k1), 3);
	d[7] = LROT((d[6] + G(a[7], b[6], c[6]) + M[6] + k1), 5);
	c[7] = LROT((c[6] + G(d[7], a[7], b[6]) + M[10] + k1), 9);
	b[7] = LROT((b[6] + G(c[7], d[7], a[7]) + M[14] + k1), 13);

	a[8] = LROT((a[7] + G(b[7], c[7], d[7]) + M[3] + k1), 3);
	d[8] = LROT((d[7] + G(a[8], b[7], c[7]) + M[7] + k1), 5);
	c[8] = LROT((c[7] + G(d[8], a[8], b[7]) + M[11] + k1), 9);
	b[8] = LROT((b[7] + G(c[8], d[8], a[8]) + M[15] + k1), 13);

	a[9] = LROT((a[8] + H(b[8], c[8], d[8]) + M[0] + k2), 3);
	d[9] = LROT((d[8] + H(a[9], b[8], c[8]) + M[8] + k2), 9);
	c[9] = LROT((c[8] + H(d[9], a[9], b[8]) + M[4] + k2), 11);
	b[9] = LROT((b[8] + H(c[9], d[9], a[9]) + M[12] + k2), 15);
	if(!bit(b[9], 32))
    {
        flag = 0;
        continue;
    }
    a[10] = LROT((a[9] + H(b[9], c[9], d[9]) + M[2] + k2), 3);
    if(!bit(a[10], 32))
    {
        flag = 0;
        continue;

    }*/
