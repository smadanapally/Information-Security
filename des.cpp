# include <stdio.h>
# include <fstream>
# include <string.h>
# include <iostream>
# include <stdlib.h>
# include <bitset>
using namespace std;

    int total[64],
        left_plain_text[17][32],
        right_plain_text[17][32],
        expansion[48],
        xor1[48],
        sub[32],
        permutation_1[32],
        pc1[56],
        message[64],
		right_sub_key[17][28],
		left_sub_key[17][28],
		converted_key[56],
		zor[17][48],
		final_permutation[64],
		encrypted_text[64];
		string str1="";
		int cipher_t[64];
	//	stringstream s;
		bool flag =true;
		 
	// sboxes
	int s1[4][16]=
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    };
 
    int s2[4][16]=
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    };
 
    int s3[4][16]=
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    };
 
    int s4[4][16]=
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    };
 
    int s5[4][16]=
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    };
 
    int s6[4][16]=
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    };
 
    int s7[4][16]=
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    };
 
    int s8[4][16]=
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    };
		
	int	encryption_key[64];
	//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0};
	int plain_text[64];
	//{1,0,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,0,0,1,0,0,1,1,0,1,0,1,0,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,1,1,0,1,0,0,0,0,0,0,0,1,0,1};
	//{1,0,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,0,0,1,0,0,1,1,0,1,0,1,0,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,1,1,0,1,0,0,0,0,0,0,0,1,0,1};

    void encryption(string key);


void encryption(string key)
{
	 for (int i = 0; i < 64; i++) 
{
    encryption_key[i] = key[i] - '0';
  //  cipher_t[i]=ctext[i]-'0';
}

	
	// 	pc1 generation
		pc1[0]=encryption_key[57-1];
		pc1[1]=encryption_key[49-1];
		pc1[2]=encryption_key[41-1];
		pc1[3]=encryption_key[33-1];
		pc1[4]=encryption_key[25-1];
		pc1[5]=encryption_key[17-1];
		pc1[6]=encryption_key[9-1];
		pc1[7]=encryption_key[1-1];
		pc1[8]=encryption_key[58-1];
		pc1[9]=encryption_key[50-1];
		pc1[10]=encryption_key[42-1];
		pc1[11]=encryption_key[34-1];
		pc1[12]=encryption_key[26-1];
		pc1[13]=encryption_key[18-1];
		pc1[14]=encryption_key[10-1];
		pc1[15]=encryption_key[2-1];
		pc1[16]=encryption_key[59-1];
		pc1[17]=encryption_key[51-1];
		pc1[18]=encryption_key[43-1];
		pc1[19]=encryption_key[35-1];
		pc1[20]=encryption_key[27-1];
		pc1[21]=encryption_key[19-1];
		pc1[22]=encryption_key[11-1];
		pc1[23]=encryption_key[3-1];
		pc1[24]=encryption_key[60-1];
		pc1[25]=encryption_key[52-1];
		pc1[26]=encryption_key[44-1];
		pc1[27]=encryption_key[36-1];
		pc1[28]=encryption_key[63-1];
		pc1[29]=encryption_key[55-1];
		pc1[30]=encryption_key[47-1];
		pc1[31]=encryption_key[39-1];
		pc1[32]=encryption_key[31-1];
		pc1[33]=encryption_key[23-1];
		pc1[34]=encryption_key[15-1];
		pc1[35]=encryption_key[7-1];
		pc1[36]=encryption_key[62-1];
		pc1[37]=encryption_key[54-1];
		pc1[38]=encryption_key[46-1];
		pc1[39]=encryption_key[38-1];
		pc1[40]=encryption_key[30-1];
		pc1[41]=encryption_key[22-1];
		pc1[42]=encryption_key[14-1];
		pc1[43]=encryption_key[6-1];
		pc1[44]=encryption_key[61-1];
		pc1[45]=encryption_key[53-1];
		pc1[46]=encryption_key[45-1];
		pc1[47]=encryption_key[37-1];
		pc1[48]=encryption_key[29-1];
		pc1[49]=encryption_key[21-1];
		pc1[50]=encryption_key[13-1];
		pc1[51]=encryption_key[5-1];
		pc1[52]=encryption_key[28-1];
		pc1[53]=encryption_key[20-1];
		pc1[54]=encryption_key[12-1];
		pc1[55]=encryption_key[4-1];
		
		for(int i=0;i<28;i++)
		{
			left_sub_key[0][i]=pc1[i];
			
		}

		for(int i=28;i<56;i++)
		{
			right_sub_key[0][i-28]=pc1[i];

		}
		
		// text manipulation
			//ip1
			message[0]=plain_text[58-1];
			message[1]=plain_text[50-1];
			message[2]=plain_text[42-1];
			message[3]=plain_text[34-1];
			message[4]=plain_text[26-1];
			message[5]=plain_text[18-1];
			message[6]=plain_text[10-1];
			message[7]=plain_text[2-1];
			message[8]=plain_text[60-1];
			message[9]=plain_text[52-1];
			message[10]=plain_text[44-1];
			message[11]=plain_text[36-1];
			message[12]=plain_text[28-1];
			message[13]=plain_text[20-1];
			message[14]=plain_text[12-1];
			message[15]=plain_text[4-1];
			message[16]=plain_text[62-1];
			message[17]=plain_text[54-1];
			message[18]=plain_text[46-1];
			message[19]=plain_text[38-1];
			message[20]=plain_text[30-1];
			message[21]=plain_text[22-1];
			message[22]=plain_text[14-1];
			message[23]=plain_text[6-1];
			message[24]=plain_text[64-1];
			message[25]=plain_text[56-1];
			message[26]=plain_text[48-1];
			message[27]=plain_text[40-1];
			message[28]=plain_text[32-1];
			message[29]=plain_text[24-1];
			message[30]=plain_text[16-1];
			message[31]=plain_text[8-1];
			message[32]=plain_text[57-1];
			message[33]=plain_text[49-1];
			message[34]=plain_text[41-1];
			message[35]=plain_text[33-1];
			message[36]=plain_text[25-1];
			message[37]=plain_text[17-1];
			message[38]=plain_text[9-1];
			message[39]=plain_text[1-1];
			message[40]=plain_text[59-1];
			message[41]=plain_text[51-1];
			message[42]=plain_text[43-1];
			message[43]=plain_text[35-1];
			message[44]=plain_text[27-1];
			message[45]=plain_text[19-1];
			message[46]=plain_text[11-1];
			message[47]=plain_text[3-1];
			message[48]=plain_text[61-1];
			message[49]=plain_text[53-1];
			message[50]=plain_text[45-1];
			message[51]=plain_text[37-1];
			message[52]=plain_text[29-1];
			message[53]=plain_text[21-1];
			message[54]=plain_text[13-1];
			message[55]=plain_text[5-1];
			message[56]=plain_text[63-1];
			message[57]=plain_text[55-1];
			message[58]=plain_text[47-1];
			message[59]=plain_text[39-1];
			message[60]=plain_text[31-1];
			message[61]=plain_text[23-1];
			message[62]=plain_text[15-1];
			message[63]=plain_text[7-1];

		// splitting text into two halfs

		for(int i=0;i<32;i++)
		{
			left_plain_text[0][i]=message[i];

		}
		

		
		for(int i=32;i<64;i++)
		{
			right_plain_text[0][i-32]=message[i];
		}
		
		// Rounds of encryption
		
		for(int round=1;round<=16;round++)
		{
			if(round!=1 && round!=2 && round!=9 && round!=16)
			{
	
				for(int j=0;j<26;j++)
				{
				
					left_sub_key[round][j]=left_sub_key[round-1][j+2];
					right_sub_key[round][j]=right_sub_key[round-1][j+2];

				}
				left_sub_key[round][26]=left_sub_key[round-1][0];
				left_sub_key[round][27]=left_sub_key[round-1][1];
				
				right_sub_key[round][26]=right_sub_key[round-1][0];
				right_sub_key[round][27]=right_sub_key[round-1][1];
			}
			else
			{
				for (int j=0;j<27;j++)
				{
					left_sub_key[round][j]=left_sub_key[round-1][j+1];
					right_sub_key[round][j]=right_sub_key[round-1][j+1];
				}
				left_sub_key[round][27]=left_sub_key[round-1][0];
				right_sub_key[round][27]=right_sub_key[round-1][0];
					
			}
			
			//concating both left and right keys
			
			for(int k=0;k<28;k++)
			{
				converted_key[k]=left_sub_key[round][k];
				
			}
	
			for(int k=0;k<28;k++)
			{
				converted_key[k+28]=right_sub_key[round][k];
	
			}
			
			//pc-2
			
				zor[round][0]=converted_key[13];
				zor[round][1]=converted_key[16];
				zor[round][2]=converted_key[10];
				zor[round][3]=converted_key[23];
				zor[round][4]=converted_key[0];
				zor[round][5]=converted_key[4];
				zor[round][6]=converted_key[2];
				zor[round][7]=converted_key[27];
				zor[round][8]=converted_key[14];
				zor[round][9]=converted_key[5];
				zor[round][10]=converted_key[20];
				zor[round][11]=converted_key[9];
				zor[round][12]=converted_key[22];
				zor[round][13]=converted_key[18];
				zor[round][14]=converted_key[11];
				zor[round][15]=converted_key[3];
				zor[round][16]=converted_key[25];
				zor[round][17]=converted_key[7];
				zor[round][18]=converted_key[15];
				zor[round][19]=converted_key[6];
				zor[round][20]=converted_key[26];
				zor[round][21]=converted_key[19];
				zor[round][22]=converted_key[12];
				zor[round][23]=converted_key[1];
				zor[round][24]=converted_key[40];
				zor[round][25]=converted_key[51];
				zor[round][26]=converted_key[30];
				zor[round][27]=converted_key[36];
				zor[round][28]=converted_key[46];
				zor[round][29]=converted_key[54];
				zor[round][30]=converted_key[29];
				zor[round][31]=converted_key[39];
				zor[round][32]=converted_key[50];
				zor[round][33]=converted_key[44];
				zor[round][34]=converted_key[32];
				zor[round][35]=converted_key[47];
				zor[round][36]=converted_key[43];
				zor[round][37]=converted_key[48];
				zor[round][38]=converted_key[38];
				zor[round][39]=converted_key[55];
				zor[round][40]=converted_key[33];
				zor[round][41]=converted_key[52];
				zor[round][42]=converted_key[45];
				zor[round][43]=converted_key[41];
				zor[round][44]=converted_key[49];
				zor[round][45]=converted_key[35];
				zor[round][46]=converted_key[28];
				zor[round][47]=converted_key[31];
    
    
    // making right text as left text for next round
	
	for(int j=0;j<32;j++)
	{
		left_plain_text[round][j]=right_plain_text[round-1][j];
	}
		
	// expansion of right_plain_text from 32 bit to 48 bit to perform xor
			expansion[0]=right_plain_text[round-1][32-1];
			expansion[1]=right_plain_text[round-1][1-1];
			expansion[2]=right_plain_text[round-1][2-1];
			expansion[3]=right_plain_text[round-1][3-1];
			expansion[4]=right_plain_text[round-1][4-1];
			expansion[5]=right_plain_text[round-1][5-1];
			expansion[6]=right_plain_text[round-1][4-1];
			expansion[7]=right_plain_text[round-1][5-1];
			expansion[8]=right_plain_text[round-1][6-1];
			expansion[9]=right_plain_text[round-1][7-1];
			expansion[10]=right_plain_text[round-1][8-1];
			expansion[11]=right_plain_text[round-1][9-1];
			expansion[12]=right_plain_text[round-1][8-1];
			expansion[13]=right_plain_text[round-1][9-1];
			expansion[14]=right_plain_text[round-1][10-1];
			expansion[15]=right_plain_text[round-1][11-1];
			expansion[16]=right_plain_text[round-1][12-1];
			expansion[17]=right_plain_text[round-1][13-1];
			expansion[18]=right_plain_text[round-1][12-1];
			expansion[19]=right_plain_text[round-1][13-1];
			expansion[20]=right_plain_text[round-1][14-1];
			expansion[21]=right_plain_text[round-1][15-1];
			expansion[22]=right_plain_text[round-1][16-1];
			expansion[23]=right_plain_text[round-1][17-1];
			expansion[24]=right_plain_text[round-1][16-1];
			expansion[25]=right_plain_text[round-1][17-1];
			expansion[26]=right_plain_text[round-1][18-1];
			expansion[27]=right_plain_text[round-1][19-1];
			expansion[28]=right_plain_text[round-1][20-1];
			expansion[29]=right_plain_text[round-1][21-1];
			expansion[30]=right_plain_text[round-1][20-1];
			expansion[31]=right_plain_text[round-1][21-1];
			expansion[32]=right_plain_text[round-1][22-1];
			expansion[33]=right_plain_text[round-1][23-1];
			expansion[34]=right_plain_text[round-1][24-1];
			expansion[35]=right_plain_text[round-1][25-1];
			expansion[36]=right_plain_text[round-1][24-1];
			expansion[37]=right_plain_text[round-1][25-1];
			expansion[38]=right_plain_text[round-1][26-1];
			expansion[39]=right_plain_text[round-1][27-1];
			expansion[40]=right_plain_text[round-1][28-1];
			expansion[41]=right_plain_text[round-1][29-1];
			expansion[42]=right_plain_text[round-1][28-1];
			expansion[43]=right_plain_text[round-1][29-1];
			expansion[44]=right_plain_text[round-1][30-1];
			expansion[45]=right_plain_text[round-1][31-1];
			expansion[46]=right_plain_text[round-1][32-1];
			expansion[47]=right_plain_text[round-1][1-1];
	
	// xor the key with right text
	
	for(int j=0;j<48;j++)
	{
		xor1[j]=zor[round][j]^expansion[j];
	
	}
	
	// sbox logic
	
	int a[8][6],k=0,m,j,p,q,count=0,g=0,v;
 
    for(m=0; m<8; m++)
    {
        for(j=0; j<6; j++)
        {
            a[m][j]=xor1[k++];
        }
    }
 
    for( m=0; m<8; m++)
    {
        p=1;
        q=0;
        k=(a[m][0]*2)+(a[m][5]*1);
        j=4;
        while(j>0)
        {
            q=q+(a[m][j]*p);
            p=p*2;
            j--;
        }
        count=m+1;
        switch(count)
        {
        case 1:
            v=s1[k][q];
            break;
        case 2:
            v=s2[k][q];
            break;
        case 3:
            v=s3[k][q];
            break;
        case 4:
            v=s4[k][q];
            break;
        case 5:
            v=s5[k][q];
            break;
        case 6:
            v=s6[k][q];
            break;
        case 7:
            v=s7[k][q];
            break;
        case 8:
            v=s8[k][q];
            break;
        }
 
        int d,m=3,a[4];
        while(v>0)
        {
            d=v%2;
            a[m--]=d;
            v=v/2;
        }
        while(m>=0)
        {
            a[m--]=0;
        }
 
        for(m=0; m<4; m++)
            sub[g++]=a[m];
    }
	
		// permutation
		
			permutation_1[0]=sub[15];
			permutation_1[1]=sub[6];
			permutation_1[2]=sub[19];
			permutation_1[3]=sub[20];
			permutation_1[4]=sub[28];
			permutation_1[5]=sub[11];
			permutation_1[6]=sub[27];
			permutation_1[7]=sub[16];
			permutation_1[8]=sub[0];
			permutation_1[9]=sub[14];
			permutation_1[10]=sub[22];
			permutation_1[11]=sub[25];
			permutation_1[12]=sub[4];
			permutation_1[13]=sub[17];
			permutation_1[14]=sub[30];
			permutation_1[15]=sub[9];
			permutation_1[16]=sub[1];
			permutation_1[17]=sub[7];
			permutation_1[18]=sub[23];
			permutation_1[19]=sub[13];
			permutation_1[20]=sub[31];
			permutation_1[21]=sub[26];
			permutation_1[22]=sub[2];
			permutation_1[23]=sub[8];
			permutation_1[24]=sub[18];
			permutation_1[25]=sub[12];
			permutation_1[26]=sub[29];
			permutation_1[27]=sub[5];
			permutation_1[28]=sub[21];
			permutation_1[29]=sub[10];
			permutation_1[30]=sub[3];
			permutation_1[31]=sub[24];
    
    
    
    // finding right text doing cor with left texgt
    
    for(int j=0;j<32;j++)
    {
    	right_plain_text[round][j]=left_plain_text[round-1][j]^permutation_1[j];
    
	}
	
	
			
	}
	
	
	for(int i=0;i<32;i++)
	{
		final_permutation[i]=right_plain_text[16][i];
	}
	
	for(int i=0;i<32;i++)
	{
		final_permutation[i+32] = left_plain_text[16][i];
	}

	
			// final_permutation permutation
			
			encrypted_text[0]=final_permutation[40-1];
			encrypted_text[1]=final_permutation[8-1];
			encrypted_text[2]=final_permutation[48-1];
			encrypted_text[3]=final_permutation[16-1];
			encrypted_text[4]=final_permutation[56-1];
			encrypted_text[5]=final_permutation[24-1];
			encrypted_text[6]=final_permutation[64-1];
			encrypted_text[7]=final_permutation[32-1];
			encrypted_text[8]=final_permutation[39-1];
			encrypted_text[9]=final_permutation[7-1];
			encrypted_text[10]=final_permutation[47-1];
			encrypted_text[11]=final_permutation[15-1];
			encrypted_text[12]=final_permutation[55-1];
			encrypted_text[13]=final_permutation[23-1];
			encrypted_text[14]=final_permutation[63-1];
			encrypted_text[15]=final_permutation[31-1];
			encrypted_text[16]=final_permutation[38-1];
			encrypted_text[17]=final_permutation[6-1];
			encrypted_text[18]=final_permutation[46-1];
			encrypted_text[19]=final_permutation[14-1];
			encrypted_text[20]=final_permutation[54-1];
			encrypted_text[21]=final_permutation[22-1];
			encrypted_text[22]=final_permutation[62-1];
			encrypted_text[23]=final_permutation[30-1];
			encrypted_text[24]=final_permutation[37-1];
			encrypted_text[25]=final_permutation[5-1];
			encrypted_text[26]=final_permutation[45-1];
			encrypted_text[27]=final_permutation[13-1];
			encrypted_text[28]=final_permutation[53-1];
			encrypted_text[29]=final_permutation[21-1];
			encrypted_text[30]=final_permutation[61-1];
			encrypted_text[31]=final_permutation[29-1];
			encrypted_text[32]=final_permutation[36-1];
			encrypted_text[33]=final_permutation[4-1];
			encrypted_text[34]=final_permutation[44-1];
			encrypted_text[35]=final_permutation[12-1];
			encrypted_text[36]=final_permutation[52-1];
			encrypted_text[37]=final_permutation[20-1];
			encrypted_text[38]=final_permutation[60-1];
			encrypted_text[39]=final_permutation[28-1];
			encrypted_text[40]=final_permutation[35-1];
			encrypted_text[41]=final_permutation[3-1];
			encrypted_text[42]=final_permutation[43-1];
			encrypted_text[43]=final_permutation[11-1];
			encrypted_text[44]=final_permutation[51-1];
			encrypted_text[45]=final_permutation[19-1];
			encrypted_text[46]=final_permutation[59-1];
			encrypted_text[47]=final_permutation[27-1];
			encrypted_text[48]=final_permutation[34-1];
			encrypted_text[49]=final_permutation[2-1];
			encrypted_text[50]=final_permutation[42-1];
			encrypted_text[51]=final_permutation[10-1];
			encrypted_text[52]=final_permutation[50-1];
			encrypted_text[53]=final_permutation[18-1];
			encrypted_text[54]=final_permutation[58-1];
			encrypted_text[55]=final_permutation[26-1];
			encrypted_text[56]=final_permutation[33-1];
			encrypted_text[57]=final_permutation[1-1];
			encrypted_text[58]=final_permutation[41-1];
			encrypted_text[59]=final_permutation[9-1];
			encrypted_text[60]=final_permutation[49-1];
			encrypted_text[61]=final_permutation[17-1];
			encrypted_text[62]=final_permutation[57-1];
			encrypted_text[63]=final_permutation[25-1];
			
		//	cout<<"encrypted_text" <<endl;
		//	for(int i=0;i<64;i++)
		//	{
		//		cout << encrypted_text[i];
		//	}
	
		/*	
			for(int nl=0;nl<64;nl++)
			{
				s << encrypted_text[nl];
  				str1 = s.str();
  				str1.str("");
				
			}
			//this thing to convert int array to string 
		/*	
			 for (int temp = 0; temp < sizeof(encrypted_text); temp++)
    str1 += itoa(encrypted_text[temp]);
  
			
			
			
			cout<<")))))))))))))))))))))))))";
			cout<<str1;
			*/
			
			for(int i=0;i<64;i++)
			{
				
				if(encrypted_text[i]!=cipher_t[i])
				{
					flag=false;
					break;
				}
				if(i==63)
				{
					flag=true;
					
			}
				//cout << encrypted_text[i];
			}
			
}


int main()
{
	
	string ptext;
	string ctext;
	string key;
	int plain_t[64];
	//enter file location here
  ifstream myfile ("File location here");
  if (myfile.is_open())
  {
  	getline(myfile,ptext);
  	cout<<ptext << '\n';
    getline (myfile,ctext);

      cout << ctext << '\n';
    myfile.close();
    for (int i = 0; i < 64; i++) 
{
    plain_text[i] = ptext[i] - '0';
    cipher_t[i]=ctext[i]-'0';
}


  }
  
  else cout << "Unable to open file"; 

	
	//long long int brute;
	
	for(long long int brute=0;brute<=72057594037927936;brute++ )
	{	
key=bitset<64>(brute).to_string();
		cout<<brute<<'\n';
		encryption(key);
		//cout<<"\nMessage: Im checking flag\n"<<flag<<"\n";
		if(flag)
			{
				
				cout<<"key found"<<'\n';
				for(int k=0;k<64;k++)
				{
					cout<<encryption_key[k];
				}
				break;
			}

}
	
	return 0;
}
