#include "FFT.h"

uint8_t sine_data [91]=
{0,  4,    9,    13,   18,   22,   27,   31,   35,   40,   44,
49,   53,   57,   62,   66,   70,   75,   79,   83,   87,
91,   96,   100,  104,  108,  112,  116,  120,  124,  127,
131,  135,  139,  143,  146,  150,  153,  157,  160,  164,
167,  171,  174,  177,  180,  183,  186,  189,  192,  195,       //Paste this at top of program
198,  201,  204,  206,  209,  211,  214,  216,  219,  221,
223,  225,  227,  229,  231,  233,  235,  236,  238,  240,
241,  243,  244,  245,  246,  247,  248,  249,  250,  251,
252,  253,  253,  254,  254,  254,  255,  255,  255,  255
};

float sine(int i)
{
  int j=i;
  float out;
  while(j<0){j=j+360;}
  while(j>360){j=j-360;}
  if(j>-1   && j<91){out= sine_data[j];}
  else if(j>90  && j<181){out= sine_data[180-j];}
  else if(j>180 && j<271){out= -sine_data[j-180];}
  else if(j>270 && j<361){out= -sine_data[360-j];}
  return (out/255);
}

float cosine(int i)
{
  int j=i;
  float out;
  while(j<0){j=j+360;}
  while(j>360){j=j-360;}
  if(j>-1   && j<91){out= sine_data[90-j];}
  else if(j>90  && j<181){out= -sine_data[j-90];}
  else if(j>180 && j<271){out= -sine_data[270-j];}
  else if(j>270 && j<361){out= sine_data[j-270];}
  return (out/255);
}

void FFT(int* in, int* out, int N, float Frequency)
{
  unsigned int data[13]={1,2,4,8,16,32,64,128,256,512,1024,2048};
  int a,c1,f,o,x;
  a=N;
  for(int i=0;i<12;i++)                 //calculating the levels
  {
    if(data[i] <= a)
    {
      o=i;
    }
  }

  int* in_ps;
  in_ps = calloc(data[o], sizeof(int));    //input for sequencing
  float* out_r;
  out_r = calloc(data[o], sizeof(float));//real part of transform
  float* out_im;
  out_im = calloc(data[o], sizeof(float));//imaginory part of transform

  x=0;
  for(int b=0;b<o;b++)                     // bit reversal
  {
    c1=data[b];
    f=data[o]/(c1+c1);
    for(int j=0;j<c1;j++)
    {
      x=x+1;
      in_ps[x]=in_ps[j]+f;
    }
  }


  for(int i=0;i<data[o];i++)            // update input array as per bit reverse order
  {
    if(in_ps[i]<a)
    {
      out_r[i]=in[in_ps[i]];
    }
    if(in_ps[i]>a)
    {
      out_r[i]=in[in_ps[i]-a];
    }
  }


  int i10,i11,n1;
  float e,c,s,tr,ti;

  for(int i=0;i<o;i++)                                    //fft
  {
	  i10=data[i];              // overall values of sine/cosine  :
	  i11=data[o]/data[i+1];    // loop with similar sine cosine:
	  e=360/data[i+1];
	  e=0-e;
	  n1=0;
	  for(int j=0;j<i10;j++)
	  {
		  c=cosine(e*j);
		  s=sine(e*j);
		  n1=j;
		  for(int k=0;k<i11;k++)
		  {
			  tr=c*out_r[i10+n1]-s*out_im[i10+n1];
			  ti=s*out_r[i10+n1]+c*out_im[i10+n1];

			  out_r[n1+i10]=out_r[n1]-tr;
			  out_r[n1]=out_r[n1]+tr;

			  out_im[n1+i10]=out_im[n1]-ti;
			  out_im[n1]=out_im[n1]+ti;

			  n1=n1+i10+i10;
		  }
	  }
  }

  for(int i=0;i<data[o-1];i++)               // getting amplitude from compex number
      {
       out_r[i]=sqrt(out_r[i]*out_r[i]+out_im[i]*out_im[i]); // to  increase the speed delete sqrt
       out_im[i]=i*Frequency/N;
      }
  x=0;       // peak detection
  for(int i=1;i<data[o-1]-1;i++)
  {
    if(out_r[i]>out_r[i-1] && out_r[i]>out_r[i+1])
    {
    	in_ps[x]=i;    //in_ps array used for storage of peak number
    	x=x+1;
    }
  }


  s=0;
  c=0;
  for(int i=0;i<x;i++)             // re arraange as per magnitude
  {
      for(int j=c;j<x;j++)
      {
          if(out_r[in_ps[i]]<out_r[in_ps[j]])
              {s=in_ps[i];
              in_ps[i]=in_ps[j];
              in_ps[j]=s;}
      }
      c=c+1;
  }
  for(int i = 0; i < data[o-1]; i++){
	  out[i] = out_r[i];
  }
  free(in_ps);
  free(out_r);
  free(out_im);
}
