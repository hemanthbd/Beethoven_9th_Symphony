/* Program to generate Beethoven's 9th Symphony in C*/

#include "tonecfg.h"

/*
 *  The 5510 DSK Board Support Library is divided into several modules, each
 *  of which has its own include file.  The file dsk5510.h must be included
 *  in every program that uses the BSL.  This example also includes
 *  dsk5510_aic23.h because it uses the AIC23 codec module.
 */
#include "dsk5510.h"
#include "dsk5510_aic23.h"

/* Length of sine wave table */
//#define SINE_TABLE_SIZE   48

/* Codec configuration settings */
DSK5510_AIC23_Config config = { \
    0x0017,  /* 0 DSK5510_AIC23_LEFTINVOL  Left line input channel volume */ \
    0x0017,  /* 1 DSK5510_AIC23_RIGHTINVOL Right line input channel volume */\
    0x01f9,  /* 2 DSK5510_AIC23_LEFTHPVOL  Left channel headphone volume */  \
    0x01f9,  /* 3 DSK5510_AIC23_RIGHTHPVOL Right channel headphone volume */ \
    0x0011,  /* 4 DSK5510_AIC23_ANAPATH    Analog audio path control */      \
    0x0000,  /* 5 DSK5510_AIC23_DIGPATH    Digital audio path control */     \
    0x0000,  /* 6 DSK5510_AIC23_POWERDOWN  Power down control */             \
    0x0043,  /* 7 DSK5510_AIC23_DIGIF      Digital audio interface format */ \
    0x0081,  /* 8 DSK5510_AIC23_SAMPLERATE Sample rate control */            \
    0x0001   /* 9 DSK5510_AIC23_DIGACT     Digital interface activation */   \
};

/* Pre-generated sine wave data, 16-bit signed samples */
  #define SINE_TABLE_SIZE   512
int sinetable[SINE_TABLE_SIZE]={
0, 
403, 
806, 
1208, 
1611, 
2013, 
2415, 
2817, 
3218, 
3619, 
4019, 
4418, 
4817, 
5215, 
5613, 
6009, 
6405, 
6800, 
7193, 
7586, 
7977, 
8367, 
8756, 
9144, 
9530, 
9915, 
10298, 
10680, 
11060, 
11438, 
11815, 
12190, 
12563, 
12934, 
13303, 
13670, 
14035, 
14398, 
14759, 
15118, 
15474, 
15828, 
16180, 
16529, 
16875, 
17219, 
17561, 
17900, 
18236, 
18569, 
18900, 
19227, 
19552, 
19874, 
20193, 
20509, 
20821, 
21131, 
21437, 
21740, 
22040, 
22336, 
22629, 
22919, 
23205, 
23488, 
23767, 
24043, 
24315, 
24583, 
24847, 
25108, 
25365, 
25618, 
25868, 
26113, 
26354, 
26592, 
26825, 
27054, 
27280, 
27501, 
27718, 
27931, 
28139, 
28343, 
28543, 
28739, 
28930, 
29117, 
29300, 
29478, 
29652, 
29821, 
29986, 
30146, 
30302, 
30453, 
30599, 
30741, 
30878, 
31010, 
31138, 
31261, 
31380, 
31493, 
31602, 
31706, 
31806, 
31900, 
31990, 
32075, 
32154, 
32230, 
32300, 
32365, 
32426, 
32481, 
32532, 
32578, 
32618, 
32654, 
32685, 
32711, 
32732, 
32748, 
32759, 
32766, 
32767, 
32763, 
32754, 
32741, 
32722, 
32699, 
32670, 
32637, 
32599, 
32555, 
32507, 
32454, 
32396, 
32333, 
32265, 
32193, 
32115, 
32033, 
31945, 
31853, 
31757, 
31655, 
31548, 
31437, 
31321, 
31200, 
31075, 
30945, 
30810, 
30671, 
30526, 
30378, 
30224, 
30066, 
29904, 
29737, 
29566, 
29390, 
29209, 
29025, 
28835, 
28642, 
28444, 
28242, 
28035, 
27825, 
27610, 
27391, 
27168, 
26940, 
26709, 
26473, 
26234, 
25991, 
25743, 
25492, 
25237, 
24978, 
24716, 
24449, 
24179, 
23905, 
23628, 
23347, 
23063, 
22775, 
22483, 
22189, 
21890, 
21589, 
21284, 
20976, 
20665, 
20351, 
20034, 
19713, 
19390, 
19064, 
18735, 
18403, 
18068, 
17731, 
17390, 
17048, 
16702, 
16354, 
16004, 
15651, 
15296, 
14939, 
14579, 
14217, 
13853, 
13487, 
13119, 
12748, 
12376, 
12002, 
11627, 
11249, 
10870, 
10489, 
10106, 
9722, 
9337, 
8950, 
8562, 
8172, 
7781, 
7390, 
6996, 
6602, 
6207, 
5811, 
5414, 
5016, 
4618, 
4219, 
3819, 
3418, 
3017, 
2616, 
2214, 
1812, 
1410, 
1007, 
604, 
201, 
-201, 
-604, 
-1007, 
-1410, 
-1812, 
-2214, 
-2616, 
-3017, 
-3418, 
-3819, 
-4219, 
-4618, 
-5016, 
-5414, 
-5811, 
-6207, 
-6602, 
-6996, 
-7390, 
-7781, 
-8172, 
-8562, 
-8950, 
-9337, 
-9722, 
-10106, 
-10489, 
-10870, 
-11249, 
-11627, 
-12002, 
-12376, 
-12748, 
-13119, 
-13487, 
-13853, 
-14217, 
-14579, 
-14939, 
-15296, 
-15651, 
-16004, 
-16354, 
-16702, 
-17048, 
-17390, 
-17731, 
-18068, 
-18403, 
-18735, 
-19064, 
-19390, 
-19713, 
-20034, 
-20351, 
-20665, 
-20976, 
-21284, 
-21589, 
-21890, 
-22189, 
-22483, 
-22775, 
-23063, 
-23347, 
-23628, 
-23905, 
-24179, 
-24449, 
-24716, 
-24978, 
-25237, 
-25492, 
-25743, 
-25991, 
-26234, 
-26473, 
-26709, 
-26940, 
-27168, 
-27391, 
-27610, 
-27825, 
-28035, 
-28242, 
-28444, 
-28642, 
-28835, 
-29025, 
-29209, 
-29390, 
-29566, 
-29737, 
-29904, 
-30066, 
-30224, 
-30378, 
-30526, 
-30671, 
-30810, 
-30945, 
-31075, 
-31200, 
-31321, 
-31437, 
-31548, 
-31655, 
-31757, 
-31853, 
-31945, 
-32033, 
-32115, 
-32193, 
-32265, 
-32333, 
-32396, 
-32454, 
-32507, 
-32555, 
-32599, 
-32637, 
-32670, 
-32699, 
-32722, 
-32741, 
-32754, 
-32763, 
-32767, 
-32766, 
-32759, 
-32748, 
-32732, 
-32711, 
-32685, 
-32654, 
-32618, 
-32578, 
-32532, 
-32481, 
-32426, 
-32365, 
-32300, 
-32230, 
-32154, 
-32075, 
-31990, 
-31900, 
-31806, 
-31706, 
-31602, 
-31493, 
-31380, 
-31261, 
-31138, 
-31010, 
-30878, 
-30741, 
-30599, 
-30453, 
-30302, 
-30146, 
-29986, 
-29821, 
-29652, 
-29478, 
-29300, 
-29117, 
-28930, 
-28739, 
-28543, 
-28343, 
-28139, 
-27931, 
-27718, 
-27501, 
-27280, 
-27054, 
-26825, 
-26592, 
-26354, 
-26113, 
-25868, 
-25618, 
-25365, 
-25108, 
-24847, 
-24583, 
-24315, 
-24043, 
-23767, 
-23488, 
-23205, 
-22919, 
-22629, 
-22336, 
-22040, 
-21740, 
-21437, 
-21131, 
-20821, 
-20509, 
-20193, 
-19874, 
-19552, 
-19227, 
-18900, 
-18569, 
-18236, 
-17900, 
-17561, 
-17219, 
-16875, 
-16529, 
-16180, 
-15828, 
-15474, 
-15118, 
-14759, 
-14398, 
-14035, 
-13670, 
-13303, 
-12934, 
-12563, 
-12190, 
-11815, 
-11438, 
-11060, 
-10680, 
-10298, 
-9915, 
-9530, 
-9144, 
-8756, 
-8367, 
-7977, 
-7586, 
-7193, 
-6800, 
-6405, 
-6009, 
-5613, 
-5215, 
-4817, 
-4418, 
-4019, 
-3619, 
-3218, 
-2817, 
-2415, 
-2013, 
-1611, 
-1208, 
-806, 
-403, 
0};


/*
 *  main() - Main code routine, initializes BSL and generates tone
 */
//octave
float notes[15]={ 1318.51  , 1318.51  , 1396.91  , 1567.98 , 1567.98   ,1396.91  , 1318.51  , 1174.66   ,1046.5, 1046.5,  1174.66,1318.51,1318.51, 1174.66,1174.66};

//Duration of each note
float time[15]={0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.6,0.2,0.4};


void main()
{
Int16 msec,i;
DSK5510_AIC23_CodecHandle hCodec;
int k;
float delta[15],sample;
for (k=0;k<15;k++) 
{
delta[k]=notes[k]/93; //delta = L*notes/Fs
}

    

    /* Initialize the board support library, must be called first */
    DSK5510_init();
     
    /* Start the codec */
    hCodec = DSK5510_AIC23_openCodec(0, &config);
   for (i=0;i<15;i++)
   {    long count=0;
   float y2=0;
    /* Generate a  sine wave for 1 second */
    for (msec = 0; msec < (93*delta[i]*time[i]); msec++) //Fs/L => 48K/512=> 93 Hz ; Going through each frequency of the note 'time' times
    {  
        for (sample = 0; sample < SINE_TABLE_SIZE; sample=sample+delta[i]) // Going through the sinetable at 'delta' intervals
        {   /* Interpolation*/
        	int y= sample; // Storing rounded-off value of sample
        	int m=sinetable[y+1]-sinetable[y]; // Baseaddress[l+1]-Baseaddress[l]
        	int b=sinetable[y]; // Baseaddress[l]
        	float x=sample-y; // Fractional Part-> (float) Baseaddress[l]- (int) Baseaddress[l]
          	float yy=(m*x)+b; // Estimating output through linear equation-> y=mx+c
           
        /*ADSR Envelope Generation corrresponding to 1 second duration of a sine-wave*/	
        	float g;
           //Equation of the ADSR -> y[n]=gx[n]=(1-g)y[n-1]  
        	if(count<1440) // Upto 30ms
        	{ g=0.00320; // g-> Rise/Decay value
        	  y2 =0.99*g + (1-g)*y2; // Rising curve
        	   }  
        	  
        	if((count>=1440)&&(count<46560)) // Between 30ms and 970ms
        	{
        	  g=0.00012; // g-> Rise/Decay value
        	  y2 =0.01*g + (1-g)*y2; // Decay Curve	 
        	  }  
        	  
        	  if(count>=46560) // From 970ms
        	{ 
        	  g=0.00320; // g-> Rise/Decay value
        	  y2 =(1-g)*y2; // Release Curve
        	  }  
        	
           /* ADSR Envelope masked point-by-point with the Interpolated result to make it smooth*/
        
        	yy=yy*y2;
          
          
            /* Send a sample to the left channel */
            while (!DSK5510_AIC23_write16(hCodec, yy));  

            /* Send a sample to the right channel */
            while (!DSK5510_AIC23_write16(hCodec,  yy)); 
     
     count++;  // Increment number of samples  
    }
    
    }
    
	}
    /* Close the codec */
    DSK5510_AIC23_closeCodec(hCodec);
}
