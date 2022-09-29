/* ********************************************************************
FILE                   : big_num_arith.c

PROGRAM DESCRIPTION    : big number basic arithmetic calculator of additions, subractions, division, multiplications and modulations, using dynamic memory allocation. 
                         Arbitrary-precision arithmetic, also called a big number arithmetic, multiple precision arithmetic, or sometimes infinite-precision arithmetic 
						 indicates that calculations are performed on numbers whose digits of precision are limited only by the available memory of the host system. 
						 This contrasts with the faster fixed-precision arithmetic found in a most arithmetic logic unit (ALU) hardware, which typically offers between 8 and 64 bits 
						 of precision. A fixed point floating-point number is also supported. Big Number is in the form of string. Arithmetic operations supported are Addition, 
						 Subtraction, Multiplications, Division and Modulus.

AUTHOR                :  K.M. Arun Kumar alias Arunkumar Murugeswaran
	 
KNOWN BUGS            :    

NOTE                  :  Compiled and Tested in Dev-C++ on Windows 7 (32 bit) Desktop OS.

    Addition: Augend + Addend = Sum.
    Subtraction: Minuend - Subtrahend = Difference.
    Multiplication: Multiplicand * Multiplier = Product. 
    Division: Dividend / Divisor = Quotient.
	Modulation: Dividend % Divisor = Remainder.
    Exponentiation: Base ^ Exponent = ___.
    Finding roots: Degree √ Radicand = Root.
	
	1: Max input number of characters of 20 is valid. 
	2: Only related input data is accepted.
	
 Reference             :
    https://www.geeksforgeeks.org/program-compute-division-upto-n-decimal-places/
	https://www.geeksforgeeks.org/multiply-large-numbers-represented-as-strings/
	https://www.geeksforgeeks.org/sum-two-large-numbers/
	https://www.geeksforgeeks.org/difference-of-two-large-numbers/
	http://rosettacode.org/wiki/Arbitrary-precision_integers_(included)#Pure_C
	https://www.geeksforgeeks.org/divide-large-number-represented-string/
	https://www.theschoolrun.com/what-is-long-division
	https://www.youtube.com/watch?v=7eWzvDlOVJ4 - Data Structure Food Order Management System
	https://www.geeksforgeeks.org/restoring-division-algorithm-unsigned-integer/
	https://www.geeksforgeeks.org/non-restoring-division-unsigned-integer/   
                          
CHANGE LOGS           : 

*****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NULL_DATA_PTR                            ((void *)0)
#define NULL_CHAR                               ('\0')

#define STATE_NO                                 (0)
#define STATE_YES                                (1)
#define STATE_NA                                 (2) 

#define SUCCESS                                  (0)
#define FAILURE                                  (1)
  
//#define TRACE                                 (1U)
#define TRACE_ERROR                             (2U)
#define TRACE_REQ                               (3U)
//#define TRACE_INFO                              (4U)
//#define TRACE_DATA                              (5U)
//#define TRACE_FLOW                              (6U)

#define MAX_OPERAND_LEN                          (20) 
#define MAX_DATA_SIZE                            (MAX_OPERAND_LEN)

#define REQ_PRECISION_DIGITS                     (10)
#define RESULT_BASED_PRECISION_DIGITS             (0)
                      
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

typedef char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long int64_t;

typedef struct
{
	const char *operand_str1;
	const char *operand_str2;
	char *proc_str1_ptr;
	char *proc_str2_ptr;
	char *result_ptr;
	uint8_t proc_str1_precision_digits;
    uint8_t proc_str2_precision_digits;
	uint8_t result_str_precision_digits;
	uint8_t proc_str1_len;
	uint8_t proc_str2_len;
	uint8_t result_alloc_size;
} big_num_datas_t;

typedef enum 
{
	BIG_NUMS_SUM_OPER = 1, BIG_NUMS_SUBTRACT_OPER, BIG_NUMS_MULTIPLY_OPER, BIG_NUMS_DIVISION_OPER, BIG_NUMS_MODULUS_OPER, EXIT_OPER,
	NUM_BIG_NUMS_OPER
} oper_t;

uint16_t Validate_Choice(int32_t *const int32_choice_ptr, const char *const choice_str_ptr);
uint16_t Str_to_Num_Conv(int32_t *const num_conv_from_str, const char *const num_in_str);
uint32_t Power_Of(const uint8_t base, const uint8_t power);
uint16_t Swap_Two_Datas(void *const data1, void *const data2, const uint8_t data_size);
uint16_t Validate_Big_Num_Data(const uint8_t big_num_arithmetic_oper, const uint8_t num_precision_digits, big_num_datas_t *const big_num_datas_ptr);
char *Big_Nums_Sum(const char *const aug_str1, const char *const add_str2);
char *Big_Nums_Subtract(const char *const min_str1, const char *const subt_str2);
char *Big_Nums_Multiply(const char *const mul_str1, const char *const mul_str2);
char *Big_Nums_Division(const char *const dividend_str1, const char *const divisor_str2, const uint8_t num_precision_digits);
char *Big_Nums_Modulus(const char *const dividend_str1, const char *const divisor_str2);
/*------------------------------------------------------------*
FUNCTION NAME  : main

DESCRIPTION    :  Driver code
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 01.01  

BUGS           :              
-*------------------------------------------------------------*/
int main() 
{ 
    char *result_ptr, read1_ptr[MAX_OPERAND_LEN], read2_ptr[MAX_OPERAND_LEN], choice_str[MAX_DATA_SIZE]; 
	double power, base, exponient;
   	int32_t int32_choice;
	
	while(1)
	{
		printf("Oper : 1 - Sum , 2 - Subtract, 3 - Multiply, 4 - Division, 5 - Modulus, 6 - Exit\n");
		printf("Enter choice : ");
		memset(choice_str, NULL_CHAR, MAX_DATA_SIZE);
		scanf("%s", choice_str);
		if((Validate_Choice(&int32_choice, choice_str)) != SUCCESS)
		{
			printf("ERR: Invalid big num operation \n");
			printf("INFO: Valid big num operation range [%u, %u] \n", BIG_NUMS_SUM_OPER, BIG_NUMS_MODULUS_OPER);
			continue;
		}
		switch(int32_choice)
		{
			case BIG_NUMS_SUM_OPER:
			   printf("Enter Augend = ");
			   scanf("%s", read1_ptr);
			   printf("Enter Addend = ");
			   scanf("%s", read2_ptr);			  
			   result_ptr = Big_Nums_Sum(read1_ptr, read2_ptr);
	           if(result_ptr != NULL_DATA_PTR)
	           {
                  printf("%s + %s = %s \n", read1_ptr, read2_ptr, result_ptr); 
                  free(result_ptr);
	           }
			break;
			case BIG_NUMS_SUBTRACT_OPER:
			   printf("Enter Minuend = ");
			   scanf("%s", read1_ptr);	
			   printf("Enter Subtrahend = ");
			   scanf("%s", read2_ptr);
			   result_ptr = Big_Nums_Subtract(read1_ptr, read2_ptr);
	           if(result_ptr != NULL_DATA_PTR)
	           {
                  printf("%s - %s = %s \n", read1_ptr, read2_ptr, result_ptr);  
                  free(result_ptr);
	           }
			break;
			case BIG_NUMS_MULTIPLY_OPER:
			   printf("Enter Multiplicand = ");
			   scanf("%s", read1_ptr);	
			   printf("Enter Multiplier = ");
			   scanf("%s", read2_ptr);
			   result_ptr = Big_Nums_Multiply(read1_ptr, read2_ptr);
	           if(result_ptr != NULL_DATA_PTR)
	           {
                  printf("%s * %s = %s \n", read1_ptr, read2_ptr, result_ptr);  
                  free(result_ptr);
	           }
			break;
			case BIG_NUMS_DIVISION_OPER:
			   printf("Enter Dividend = ");
			   scanf("%s", read1_ptr);	
			   printf("Enter Divisor = ");
			   scanf("%s", read2_ptr);
			   result_ptr = Big_Nums_Division(read1_ptr, read2_ptr, REQ_PRECISION_DIGITS);
	           if(result_ptr != NULL_DATA_PTR)
	           {
                  printf("%s / %s = %s \n", read1_ptr, read2_ptr, result_ptr);  
                  free(result_ptr);
	           }
			break;
			case BIG_NUMS_MODULUS_OPER:
			   printf("Enter Dividend = ");
			   scanf("%s", read1_ptr);	
			   printf("Enter Divisor = ");
			   scanf("%s", read2_ptr);
			   result_ptr = Big_Nums_Modulus(read1_ptr, read2_ptr);
	           if(result_ptr != NULL_DATA_PTR)
	           {
                  printf("%s %% %s = %s \n", read1_ptr, read2_ptr, result_ptr);  
                  free(result_ptr);
	           }
			break;
			case EXIT_OPER:
			return SUCCESS;
			//break;
			default:
			  printf("Invalid oper \n");               			
		}
		printf("\n\n");
	}
    return SUCCESS; 
}

/*------------------------------------------------------------*
FUNCTION NAME  : Str_to_Num_Conv

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : digits are extracted from left to right format from digit in num_in_str

Func ID        : 02.04  

BUGS           :  
-*------------------------------------------------------------*/
uint16_t Str_to_Num_Conv( int32_t *const num_conv_from_str, const char *const num_in_str)
{	
	 int32_t num = 0;
	 uint32_t place;
	 int16_t cur_unit;
	 uint8_t num_chars = 0, base = 10, pos = 0, start_num_pos = 0 ;
	
	 if(num_conv_from_str == NULL_DATA_PTR || num_in_str == NULL_DATA_PTR )
	 {
		 #ifdef TRACE_ERROR
		   printf("ERR: data are null ptr \n");
		#endif
		return FAILURE;
	 }
	 if(num_in_str[0] >= '0' && num_in_str[0] <= '9')
	 {
		  start_num_pos = 0;
	 }
	 else
	 {
		 *num_conv_from_str = 0;
		 #ifdef TRACE_ERROR
		    printf("ERR: invalid char: %c \n", num_in_str[0]);
		 #endif
         return FAILURE; 
	 }		 
	 num_chars = strlen(num_in_str + start_num_pos);
	 if(num_chars == 0)
	 {
		 *num_conv_from_str = 0;
		 #ifdef TRACE_ERROR
		    printf("ERR: data empty \n");
		 #endif
         return FAILURE; 
	 }
	 pos = start_num_pos; 	     
     for( place = Power_Of(base, num_chars - 1); place >= 1; place /= base, ++pos )
     {
     	 cur_unit = num_in_str[pos] - '0';
    	 if(cur_unit < 0 ||  cur_unit > 9 )
    	 {
	    	 *num_conv_from_str = 0;
             #ifdef TRACE_ERROR
		       printf("ERR: invalid char at data[%d] = %c \n", pos, num_in_str[pos]);
		     #endif
             return FAILURE; 
	     }		 
         num += (cur_unit * place);		      
     }
	 if(num_in_str[0] == '-')
	 {
		 *num_conv_from_str = -num;  
	 }
	 else
	 {
	     *num_conv_from_str = num; 
	 }
     return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Power_Of

DESCRIPTION    :
								
INPUT          :

OUTPUT         : 

NOTE           : 

Func ID        : 02.10 

Bugs           :   
-*------------------------------------------------------------*/
uint32_t Power_Of(const uint8_t base, const uint8_t power )
{
    uint32_t power_val = 1;
    uint8_t i = 0;
  
    if(power == 0)
    {
       return power_val;
    }
    for(i = 1; i <= power; ++i)
    {
      power_val *= base;
    }
    return power_val;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Validate_Choice

DESCRIPTION    : 
								
INPUT          : 

OUTPUT         : 

NOTE           :               

Func ID        : 01.02  

BUGS           :              
-*------------------------------------------------------------*/
uint16_t Validate_Choice(int32_t *const int32_choice_ptr, const char *const choice_str_ptr)
{
	if((Str_to_Num_Conv(int32_choice_ptr, choice_str_ptr)) != SUCCESS)
	{
		return FAILURE;
	}
	if(*int32_choice_ptr < BIG_NUMS_SUM_OPER || *int32_choice_ptr >= NUM_BIG_NUMS_OPER)
	{
		return FAILURE;
	}
	return SUCCESS;
}
/*------------------------------------------------------------*
FUNCTION NAME  : Swap_Two_Datas

DESCRIPTION    : 
								
INPUT          : 

OUTPUT         : 

NOTE           :               

Func ID        : 01.02  

BUGS           :              
-*------------------------------------------------------------*/
uint16_t Swap_Two_Datas(void *const data1, void *const data2, const uint8_t data_size)
{
	char temp[MAX_DATA_SIZE];
	
	if(data1 == NULL_DATA_PTR || data2 == NULL_DATA_PTR)
	{
		return FAILURE;
	}
	if(data_size == 0)
	{
		return FAILURE;
	}
    memcpy(temp, data1, data_size);
    memcpy(data1, data2, data_size);
    memcpy(data2, temp, data_size);
	return SUCCESS;
}
/*------------------------------------------------------------*
FUNCTION NAME  :  Validate_Big_Num_Data

DESCRIPTION    :  
								
INPUT          : 

OUTPUT         : 

NOTE           :  Caller is responsible for freeing memory.                  

Func ID        : 01.03  

BUGS           :              
-*------------------------------------------------------------*/ 
uint16_t Validate_Big_Num_Data(const uint8_t big_num_arithmetic_oper, const uint8_t num_precision_digits, big_num_datas_t *const big_num_datas_ptr)
{
	const char *str1_ptr, *str2_ptr;
	int16_t proc_str1_ptr_pos, proc_str2_ptr_pos, result_ptr_pos;
	uint8_t proc_bit_field = 0, req_num_0_char_digits = 0;
	
	if((big_num_datas_ptr == NULL_DATA_PTR) || (big_num_datas_ptr->operand_str1 == NULL_DATA_PTR || big_num_datas_ptr->operand_str2 == NULL_DATA_PTR))
	{
		#ifdef TRACE_ERROR
	      printf("ERR: operand_str1 or operand_str2 is null \n");
		#endif  
		return FAILURE;	
	}
	big_num_datas_ptr->proc_str1_len = strlen(big_num_datas_ptr->operand_str1);
	big_num_datas_ptr->proc_str2_len = strlen(big_num_datas_ptr->operand_str2);	
	big_num_datas_ptr->proc_str1_precision_digits = 0;
	big_num_datas_ptr->proc_str2_precision_digits = 0;
	big_num_datas_ptr->result_str_precision_digits = 0;
	big_num_datas_ptr->result_ptr = NULL_DATA_PTR;
	big_num_datas_ptr->proc_str1_ptr = NULL_DATA_PTR;
	big_num_datas_ptr->proc_str2_ptr = NULL_DATA_PTR;
	big_num_datas_ptr->result_alloc_size = 0;
    if(big_num_datas_ptr->proc_str1_len == 0 || big_num_datas_ptr->proc_str2_len == 0)
	{
		#ifdef TRACE_ERROR
		   printf("ERR: operand_str1 or operand_str2 is empty \n");
		#endif
		return FAILURE;
	}		
	if(big_num_datas_ptr->proc_str1_len == 1 && (big_num_datas_ptr->operand_str1[0] < '0' || big_num_datas_ptr->operand_str1[0] > '9'))
	{
		#ifdef TRACE_ERROR
		   printf("ERR: operand_str1 has only non numeric char \n");
		#endif
		return FAILURE;
	}
	if(big_num_datas_ptr->proc_str2_len == 1 && (big_num_datas_ptr->operand_str2[0] < '0' || big_num_datas_ptr->operand_str2[0] > '9'))
	{
		#ifdef TRACE_ERROR
		   printf("ERR: operand_str2 has only non numeric char \n");
		#endif
		return FAILURE;
	}
    if(big_num_datas_ptr->operand_str1[0] == '-' || big_num_datas_ptr->operand_str1[0] == '+') 
    { 
        str1_ptr = big_num_datas_ptr->operand_str1 + 1;	
		--big_num_datas_ptr->proc_str1_len;
    } 
    else 
	{
		str1_ptr = big_num_datas_ptr->operand_str1;		
	}
    if(big_num_datas_ptr->operand_str2[0] == '-' || big_num_datas_ptr->operand_str2[0] == '+') 
    { 
        str2_ptr = big_num_datas_ptr->operand_str2 + 1;
        --big_num_datas_ptr->proc_str2_len;		
    }
	else
	{
		str2_ptr = big_num_datas_ptr->operand_str2;
	}
    switch(big_num_arithmetic_oper)
	{
		case BIG_NUMS_SUM_OPER:
		case BIG_NUMS_SUBTRACT_OPER:
		   for(proc_str1_ptr_pos = 0; proc_str1_ptr_pos < big_num_datas_ptr->proc_str1_len; ++proc_str1_ptr_pos)
	       {
	    	  if(str1_ptr[proc_str1_ptr_pos] != '0')
		      {
			      break;
		      }		
	       }
		   for(proc_str2_ptr_pos = 0; proc_str2_ptr_pos < big_num_datas_ptr->proc_str2_len; ++proc_str2_ptr_pos)
	       {
	    	  if(str2_ptr[proc_str2_ptr_pos] != '0')
		      {
			     break;
		      }	
	       }
		   if(proc_str1_ptr_pos == big_num_datas_ptr->proc_str1_len && proc_str2_ptr_pos == big_num_datas_ptr->proc_str2_len) 
		   {
			   big_num_datas_ptr->result_alloc_size = 2;
			   big_num_datas_ptr->result_ptr = calloc(big_num_datas_ptr->result_alloc_size, sizeof(char));
			   if(big_num_datas_ptr->result_ptr == NULL_DATA_PTR)
			   {
				   #ifdef TRACE_ERROR
				       printf("ERR: memory allocation failed \n");
				   #endif
				   return FAILURE;
			   }
		       big_num_datas_ptr->result_ptr[0] = '0';
		       big_num_datas_ptr->result_ptr[1] = NULL_CHAR;
		       return SUCCESS;
		   }
		   if(proc_str1_ptr_pos != big_num_datas_ptr->proc_str1_len)
		   {
			   str1_ptr += proc_str1_ptr_pos;	          
		   }
		   else 
		   {
			   str1_ptr += (big_num_datas_ptr->proc_str1_len - 1);	           	
		   }
		   big_num_datas_ptr->proc_str1_len = strlen(str1_ptr);	
		   if(proc_str2_ptr_pos != big_num_datas_ptr->proc_str2_len)
		   {
			    str2_ptr += proc_str2_ptr_pos;  
		   }
           else
		   {
			   str2_ptr += (big_num_datas_ptr->proc_str2_len - 1);	    
		   }
           big_num_datas_ptr->proc_str2_len = strlen(str2_ptr); 		   
		break;
		case BIG_NUMS_MULTIPLY_OPER:
		   for(proc_str1_ptr_pos = 0; proc_str1_ptr_pos < big_num_datas_ptr->proc_str1_len; ++proc_str1_ptr_pos)
	       {
	    	  if(str1_ptr[proc_str1_ptr_pos] != '0')
		      {
			     break;
		      }		
	       }	
	       if(proc_str1_ptr_pos == big_num_datas_ptr->proc_str1_len)
	       {
			   big_num_datas_ptr->result_alloc_size = 2;
			   big_num_datas_ptr->result_ptr = calloc(big_num_datas_ptr->result_alloc_size, sizeof(char));
			   if(big_num_datas_ptr->result_ptr == NULL_DATA_PTR)
			   {
				   #ifdef TRACE_ERROR
				       printf("ERR: memory allocation failed \n");
				   #endif
				   return FAILURE;
			   }
		       big_num_datas_ptr->result_ptr[0] = '0';
		       big_num_datas_ptr->result_ptr[1] = NULL_CHAR;
		       return SUCCESS;
	       }
	       str1_ptr += proc_str1_ptr_pos;
	       big_num_datas_ptr->proc_str1_len -= proc_str1_ptr_pos;	
	       for(proc_str2_ptr_pos = 0; proc_str2_ptr_pos < big_num_datas_ptr->proc_str2_len; ++proc_str2_ptr_pos)
	       {
	    	  if(str2_ptr[proc_str2_ptr_pos] != '0')
		      {
			     break;
		      }	
	       }
	       if(proc_str2_ptr_pos == big_num_datas_ptr->proc_str2_len)
	       {
		      big_num_datas_ptr->result_alloc_size = 2;
			  big_num_datas_ptr->result_ptr = calloc(big_num_datas_ptr->result_alloc_size, sizeof(char));
			  big_num_datas_ptr->result_ptr[0] = '0';
			  big_num_datas_ptr->result_ptr[1] = NULL_CHAR;
		      return SUCCESS;
	      }
	      big_num_datas_ptr->proc_str2_len -= proc_str2_ptr_pos;
	      str2_ptr += proc_str2_ptr_pos;		 
		break;
        case BIG_NUMS_DIVISION_OPER:
		case BIG_NUMS_MODULUS_OPER:
		   for(proc_str2_ptr_pos = 0; proc_str2_ptr_pos < big_num_datas_ptr->proc_str2_len; ++proc_str2_ptr_pos)
	       {
	    	  if(str2_ptr[proc_str2_ptr_pos] != '0')
		      {
			     break;
		      }	
	       }
	       if(proc_str2_ptr_pos == big_num_datas_ptr->proc_str2_len)
	       {
		       proc_bit_field |= (1 << 0);
	       }
		   else
		   {
	           big_num_datas_ptr->proc_str2_len -= proc_str2_ptr_pos;
	           str2_ptr += proc_str2_ptr_pos;
		   }
		   for(proc_str1_ptr_pos = 0; proc_str1_ptr_pos < big_num_datas_ptr->proc_str1_len; ++proc_str1_ptr_pos)
	       {
	    	   if(str1_ptr[proc_str1_ptr_pos] != '0')
		       {
			       break;
		       }		
	       } 
	       if(proc_str1_ptr_pos == big_num_datas_ptr->proc_str1_len)
	       {
			   if((proc_bit_field & (1 << 0)))
			   {
				   // 0/0
				   printf("ERR: 0 / 0 = indetermined \n");
				  return FAILURE;
			   }
			   big_num_datas_ptr->result_alloc_size = num_precision_digits + 1 + 1 + 1;		
	           big_num_datas_ptr->result_ptr = calloc(big_num_datas_ptr->result_alloc_size, sizeof(char));
		       if(big_num_datas_ptr->result_ptr == NULL_DATA_PTR)
		       {
		        	#ifdef TRACE_ERROR
		               printf("ERR: div - memory alloc failed \n");
		            #endif
			        return FAILURE;
		        }				
		        for(result_ptr_pos = 0; result_ptr_pos < num_precision_digits + 1 + 1; ++result_ptr_pos)
		        {
			       if(result_ptr_pos == 1)
			       {
			        	big_num_datas_ptr->result_ptr[result_ptr_pos] = '.';
				        continue;
			       }
			       big_num_datas_ptr->result_ptr[result_ptr_pos] = '0';
		        }
		        big_num_datas_ptr->result_ptr[result_ptr_pos] = NULL_CHAR;
				return SUCCESS;	
	       }		   
        break; 		
    }
	/* convert from ASCII string numbers, into numeric */
	big_num_datas_ptr->proc_str1_ptr = malloc(big_num_datas_ptr->proc_str1_len + 1); 
	if(big_num_datas_ptr->proc_str1_ptr == NULL_DATA_PTR)
	{
		#ifdef TRACE_ERROR
		   printf("ERR: memory allocation failed \n");
		#endif
		return FAILURE;
	}
	strcpy(big_num_datas_ptr->proc_str1_ptr, str1_ptr); 
    big_num_datas_ptr->proc_str1_precision_digits = 0;
    proc_str1_ptr_pos = 0;
	while (proc_str1_ptr_pos < big_num_datas_ptr->proc_str1_len) 
	{ 
	   if(big_num_datas_ptr->proc_str1_ptr[proc_str1_ptr_pos] >= '0' && big_num_datas_ptr->proc_str1_ptr[proc_str1_ptr_pos] <= '9')
	   {
	   	   big_num_datas_ptr->proc_str1_ptr[proc_str1_ptr_pos] -= '0';		   
		   ++proc_str1_ptr_pos;	
		   continue;    
	   }
	   if(big_num_datas_ptr->proc_str1_precision_digits == 0 && big_num_datas_ptr->proc_str1_ptr[proc_str1_ptr_pos] == '.' )
	   {
		    --big_num_datas_ptr->proc_str1_len;
            memmove(big_num_datas_ptr->proc_str1_ptr + proc_str1_ptr_pos , big_num_datas_ptr->proc_str1_ptr + proc_str1_ptr_pos + 1, (big_num_datas_ptr->proc_str1_len - proc_str1_ptr_pos));
          	big_num_datas_ptr->proc_str1_ptr[big_num_datas_ptr->proc_str1_len] = NULL_CHAR;
          	#ifdef TRACE_DATA
          	   printf("TRA: decimal_pos: %u, frac_str1 = %s \n", proc_str1_ptr_pos, big_num_datas_ptr->proc_str1_ptr + proc_str1_ptr_pos);
          	#endif
            big_num_datas_ptr->proc_str1_precision_digits = big_num_datas_ptr->proc_str1_len - proc_str1_ptr_pos;
            continue;
	   }
	   #ifdef TRACE_ERROR
	      printf("ERR: str_1 has invalid char : %c at pos : %u \n", big_num_datas_ptr->proc_str1_ptr[proc_str1_ptr_pos], proc_str1_ptr_pos);
	   #endif
	   big_num_datas_ptr->proc_str1_precision_digits = 0;
	   if(big_num_datas_ptr->proc_str1_ptr)
	   {
	       free(big_num_datas_ptr->proc_str1_ptr);
	       big_num_datas_ptr->proc_str1_ptr = NULL_DATA_PTR;
	   }
	   return FAILURE;       
	}
	big_num_datas_ptr->proc_str2_ptr = malloc(big_num_datas_ptr->proc_str2_len + 1);
	if(big_num_datas_ptr->proc_str2_ptr == NULL_DATA_PTR)
	{
	   if(big_num_datas_ptr->proc_str1_ptr)
	   {
	      free(big_num_datas_ptr->proc_str1_ptr);
	      big_num_datas_ptr->proc_str1_ptr = NULL_DATA_PTR;
	   }
	   return FAILURE;
	}
	strcpy(big_num_datas_ptr->proc_str2_ptr, str2_ptr); 
	big_num_datas_ptr->proc_str2_precision_digits = 0;
	proc_str2_ptr_pos = 0;
	while( proc_str2_ptr_pos < big_num_datas_ptr->proc_str2_len )
	{
	   if(big_num_datas_ptr->proc_str2_ptr[proc_str2_ptr_pos] >= '0' && big_num_datas_ptr->proc_str2_ptr[proc_str2_ptr_pos] <= '9')
	   {
	   	   big_num_datas_ptr->proc_str2_ptr[proc_str2_ptr_pos] -= '0';	
	   	   ++proc_str2_ptr_pos;
		   continue;	    
	   }
	   if(big_num_datas_ptr->proc_str2_precision_digits == 0 && big_num_datas_ptr->proc_str2_ptr[proc_str2_ptr_pos] == '.' )
	   {
		   --big_num_datas_ptr->proc_str2_len;
		   memmove(big_num_datas_ptr->proc_str2_ptr + proc_str2_ptr_pos , big_num_datas_ptr->proc_str2_ptr + proc_str2_ptr_pos + 1, (big_num_datas_ptr->proc_str2_len - proc_str2_ptr_pos)); 
		   big_num_datas_ptr->proc_str2_ptr[big_num_datas_ptr->proc_str2_len] = NULL_CHAR;
		   	#ifdef TRACE_DATA
          	   printf("TRA: decimal_pos: %u, frac_str2 = %s \n", proc_str2_ptr_pos, big_num_datas_ptr->proc_str2_ptr + proc_str2_ptr_pos);
          	#endif
	    	big_num_datas_ptr->proc_str2_precision_digits = big_num_datas_ptr->proc_str2_len - proc_str2_ptr_pos;	  		  
		   continue;
	   }
	   #ifdef TRACE_ERROR
	      printf("ERR: str_2 has invalid char : %c at pos : %u \n", big_num_datas_ptr->proc_str2_ptr[proc_str2_ptr_pos], proc_str2_ptr_pos);
	   #endif
	   if(big_num_datas_ptr->proc_str1_ptr)
	   {
	      free(big_num_datas_ptr->proc_str1_ptr);
	      big_num_datas_ptr->proc_str1_ptr = NULL_DATA_PTR;
	   }
	   if(big_num_datas_ptr->proc_str2_ptr)
	   {
	      free(big_num_datas_ptr->proc_str2_ptr);	
	      big_num_datas_ptr->proc_str2_ptr = NULL_DATA_PTR;
	   }
	   return FAILURE; 
	}
	switch(big_num_arithmetic_oper) 
	{
		case BIG_NUMS_SUM_OPER:
		case BIG_NUMS_SUBTRACT_OPER:
		  for(proc_str1_ptr_pos = 0; proc_str1_ptr_pos < big_num_datas_ptr->proc_str1_len; ++proc_str1_ptr_pos) 
	       {
			   if(big_num_datas_ptr->proc_str1_ptr[proc_str1_ptr_pos] != 0)
			   {
				   break;
			   }
		   }
		   if(proc_str1_ptr_pos < big_num_datas_ptr->proc_str1_len)
		   {
			    break;			  
		   }
		   proc_bit_field |= (1 << 1);
           for(proc_str2_ptr_pos = 0; proc_str2_ptr_pos < big_num_datas_ptr->proc_str2_len; ++proc_str2_ptr_pos) 
	       {
			   if(big_num_datas_ptr->proc_str2_ptr[proc_str2_ptr_pos] != 0)
			   {
				   break;
			   }
		   }
		   if(proc_str2_ptr_pos < big_num_datas_ptr->proc_str2_len)
		   {
			   break;
		   }
           if((proc_bit_field & (1 << 1)))
		   {
			   proc_bit_field |= (1 << 2);
			   req_num_0_char_digits = 2;
			   goto big_num_result_proc;
		   }			   
		break;
		case BIG_NUMS_MULTIPLY_OPER:
		   for(proc_str1_ptr_pos = 0; proc_str1_ptr_pos < big_num_datas_ptr->proc_str1_len; ++proc_str1_ptr_pos) 
	       {
			   if(big_num_datas_ptr->proc_str1_ptr[proc_str1_ptr_pos] != 0)
			   {
				   break;
			   }
		   }
		   if(proc_str1_ptr_pos == big_num_datas_ptr->proc_str1_len)
		   {
			   proc_bit_field |= (1 << 2);
			   req_num_0_char_digits = 2;
			   goto big_num_result_proc;
	       }
		   for(proc_str2_ptr_pos = 0; proc_str2_ptr_pos < big_num_datas_ptr->proc_str2_len; ++proc_str2_ptr_pos) 
	       {
			   if(big_num_datas_ptr->proc_str2_ptr[proc_str2_ptr_pos] != 0)
			   {
				   break;
			   }
		   }
		   if(proc_str2_ptr_pos == big_num_datas_ptr->proc_str2_len)
		   {
		       proc_bit_field |= (1 << 2);
			   req_num_0_char_digits = 2;
			   goto big_num_result_proc;
	       }		   
		break;
		case BIG_NUMS_DIVISION_OPER:
		case BIG_NUMS_MODULUS_OPER:
		   if(big_num_arithmetic_oper == BIG_NUMS_MODULUS_OPER)
		   {
			   if(big_num_datas_ptr->proc_str1_precision_digits != 0 || big_num_datas_ptr->proc_str2_precision_digits != 0)
			   {
				   #ifdef TRACE_ERROR
			         printf("ERR: %s or %s are non integer \n", big_num_datas_ptr->operand_str1, big_num_datas_ptr->operand_str2);
			       #endif
				   if(big_num_datas_ptr->proc_str1_ptr)
	               {
	                   free(big_num_datas_ptr->proc_str1_ptr);
	                   big_num_datas_ptr->proc_str1_ptr = NULL_DATA_PTR;
	               }
	               if(big_num_datas_ptr->proc_str2_ptr)
	               {
	                   free(big_num_datas_ptr->proc_str2_ptr);	
	                   big_num_datas_ptr->proc_str2_ptr = NULL_DATA_PTR;
	               }
	                return FAILURE; 
			   }
		   }
		   for(proc_str2_ptr_pos = 0; proc_str2_ptr_pos < big_num_datas_ptr->proc_str2_len; ++proc_str2_ptr_pos) 
	       {
			   if(big_num_datas_ptr->proc_str2_ptr[proc_str2_ptr_pos] != 0)
			   {
				   break;
			   }
		   }
		   if(proc_str2_ptr_pos == big_num_datas_ptr->proc_str2_len)
		   {
		      proc_bit_field = (1 << 0);
	       }
		   else
		   {
		       proc_str1_ptr_pos = proc_str2_ptr_pos;
		       for(proc_str2_ptr_pos = 0; proc_str2_ptr_pos < big_num_datas_ptr->proc_str2_len; ++proc_str2_ptr_pos) 
	           {
			       big_num_datas_ptr->proc_str2_ptr[proc_str2_ptr_pos] += '0';
		       }
               big_num_datas_ptr->proc_str2_ptr[proc_str2_ptr_pos] = NULL_CHAR;
		       big_num_datas_ptr->proc_str2_len -= proc_str1_ptr_pos;
               memmove(big_num_datas_ptr->proc_str2_ptr, big_num_datas_ptr->proc_str2_ptr + proc_str1_ptr_pos, big_num_datas_ptr->proc_str2_len + 1 );
               for(proc_str2_ptr_pos = 0; proc_str2_ptr_pos < big_num_datas_ptr->proc_str2_len; ++proc_str2_ptr_pos) 
	           {
			       big_num_datas_ptr->proc_str2_ptr[proc_str2_ptr_pos] -= '0';
		       }
		       big_num_datas_ptr->proc_str2_ptr[proc_str2_ptr_pos] = NULL_CHAR;
		   }
		   for(proc_str1_ptr_pos = 0; proc_str1_ptr_pos < big_num_datas_ptr->proc_str1_len; ++proc_str1_ptr_pos) 
	       {
			   if(big_num_datas_ptr->proc_str1_ptr[proc_str1_ptr_pos] != 0)
			   {
				   break;
			   }
		   }
		   if(proc_str1_ptr_pos == big_num_datas_ptr->proc_str1_len)
		   {
			   if((proc_bit_field & (1 << 0)))
			   {
				    printf("ERR: 0 / 0 = indetermined \n");				    
					if(big_num_datas_ptr->proc_str1_ptr)
			        {
			           free(big_num_datas_ptr->proc_str1_ptr);
			           big_num_datas_ptr->proc_str1_ptr = NULL_DATA_PTR;
			        }
			        if(big_num_datas_ptr->proc_str2_ptr)
			        {
	                    free(big_num_datas_ptr->proc_str2_ptr);	
			            big_num_datas_ptr->proc_str2_ptr = NULL_DATA_PTR;
			        }
				    return FAILURE;
			   }
			   proc_bit_field |= (1 << 2);
			   req_num_0_char_digits = num_precision_digits + 1;
			   goto big_num_result_proc;
		   }
		   if((proc_bit_field & (1 << 0)))
		   {
			    printf("ERR: %s / 0 = ", big_num_datas_ptr->operand_str1);
				if(big_num_datas_ptr->operand_str1[0] == '-')
				{
					printf("negative Infinity \n");
				}
				else
				{
					printf("positive Infinity \n");
				}
				if(big_num_datas_ptr->proc_str1_ptr)
			    {
			          free(big_num_datas_ptr->proc_str1_ptr);
			          big_num_datas_ptr->proc_str1_ptr = NULL_DATA_PTR;
			    }
			    if(big_num_datas_ptr->proc_str2_ptr)
			    {
	                 free(big_num_datas_ptr->proc_str2_ptr);	
			         big_num_datas_ptr->proc_str2_ptr = NULL_DATA_PTR;
			    }
			   return FAILURE;
		   }
		   proc_str2_ptr_pos = proc_str1_ptr_pos;
		   for(proc_str1_ptr_pos = 0; proc_str1_ptr_pos < big_num_datas_ptr->proc_str1_len; ++proc_str1_ptr_pos) 
	       {
			   big_num_datas_ptr->proc_str1_ptr[proc_str1_ptr_pos] += '0';
		   }
           big_num_datas_ptr->proc_str1_ptr[proc_str1_ptr_pos] = NULL_CHAR;
		   big_num_datas_ptr->proc_str1_len -= proc_str2_ptr_pos;
           memmove(big_num_datas_ptr->proc_str1_ptr, big_num_datas_ptr->proc_str1_ptr + proc_str2_ptr_pos, big_num_datas_ptr->proc_str1_len + 1 );
           for(proc_str1_ptr_pos = 0; proc_str1_ptr_pos < big_num_datas_ptr->proc_str1_len; ++proc_str1_ptr_pos) 
	       {
			   big_num_datas_ptr->proc_str1_ptr[proc_str1_ptr_pos] -= '0';
		   }
		   big_num_datas_ptr->proc_str1_ptr[proc_str1_ptr_pos] = NULL_CHAR;
		break;   
	}
	big_num_result_proc:
	if((proc_bit_field & (1 << 2)))
	{
		 // result_alloc_size included for '.' char 
	      big_num_datas_ptr->result_alloc_size = req_num_0_char_digits + 1 + 1;		
	      big_num_datas_ptr->result_ptr = calloc(big_num_datas_ptr->result_alloc_size, sizeof(char));
	      if(big_num_datas_ptr->result_ptr == NULL_DATA_PTR)
	      {
		      	#ifdef TRACE_ERROR
		             printf("ERR: memory alloc failed \n");
		        #endif
    		    if(big_num_datas_ptr->proc_str1_ptr)
			    {
			         free(big_num_datas_ptr->proc_str1_ptr);
			         big_num_datas_ptr->proc_str1_ptr = NULL_DATA_PTR;
			    }
			    if(big_num_datas_ptr->proc_str2_ptr)
			    {
	                 free(big_num_datas_ptr->proc_str2_ptr);	
			         big_num_datas_ptr->proc_str2_ptr = NULL_DATA_PTR;
			    }
			    return FAILURE;
		  }
		  for(result_ptr_pos = 0; result_ptr_pos < big_num_datas_ptr->result_alloc_size - 1; ++result_ptr_pos)
	      {
	          if(result_ptr_pos == 1)
		      {
			       	big_num_datas_ptr->result_ptr[result_ptr_pos] = '.';
			        continue;
			  }
			  big_num_datas_ptr->result_ptr[result_ptr_pos] = '0';
		 }
		 big_num_datas_ptr->result_ptr[result_ptr_pos] = NULL_CHAR;
		 if(big_num_datas_ptr->proc_str1_ptr)
		 {
		      free(big_num_datas_ptr->proc_str1_ptr);
		      big_num_datas_ptr->proc_str1_ptr = NULL_DATA_PTR;
		 }
		 if(big_num_datas_ptr->proc_str2_ptr)
		 {
	          free(big_num_datas_ptr->proc_str2_ptr);	
		      big_num_datas_ptr->proc_str2_ptr = NULL_DATA_PTR;
		 }
		 return SUCCESS;
	 }
	#ifdef TRACE_DATA
	   printf("TRA: proc_str1_len = %u, proc_str2_len = %u \n", big_num_datas_ptr->proc_str1_len, big_num_datas_ptr->proc_str2_len);	  
	#endif
	return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Big_Nums_Multiply

DESCRIPTION    :  Multiplies str1 and str2, and find result
								
INPUT          : 

OUTPUT         : 

NOTE           :  Caller is responsible for freeing result memory.                  

Func ID        : 01.03  

BUGS           :              
-*------------------------------------------------------------*/  
char *Big_Nums_Multiply(const char *const mul_str1, const char *const mul_str2) 
{ 
    big_num_datas_t multiply_big_num_datas;
	char *temp_ptr;
	int16_t proc_str1_ptr_pos = 0, proc_str2_ptr_pos = 0, result_ptr_pos = 0;
	uint8_t i, result_ptr_init_pos;
	
	#ifdef TRACE_FLOW
	   printf("TRA: In Big num, %s * %s \n", mul_str1, mul_str2);
	#endif
	multiply_big_num_datas.operand_str1 = mul_str1;
	multiply_big_num_datas.operand_str2 = mul_str2;
	if((Validate_Big_Num_Data(BIG_NUMS_MULTIPLY_OPER, RESULT_BASED_PRECISION_DIGITS, &multiply_big_num_datas)) != SUCCESS)
    {
		return NULL_DATA_PTR;
	}
	if(multiply_big_num_datas.result_ptr != NULL_DATA_PTR)
	{
		return multiply_big_num_datas.result_ptr;
	}
	//result_alloc_size is included for NULL_CHAR at end of result_ptr
	multiply_big_num_datas.result_alloc_size = multiply_big_num_datas.proc_str1_len + multiply_big_num_datas.proc_str2_len + 1;
	i = 0;
    if((mul_str1[0] == '-' && mul_str2[0] != '-') || (mul_str1[0] != '-' && mul_str2[0] == '-'))
	{
		i = 1;
		++multiply_big_num_datas.result_alloc_size;				 
	}
	if(multiply_big_num_datas.proc_str1_precision_digits != 0 || multiply_big_num_datas.proc_str2_precision_digits != 0 )
	{
		multiply_big_num_datas.result_str_precision_digits = multiply_big_num_datas.proc_str1_precision_digits + multiply_big_num_datas.proc_str2_precision_digits; 
		//result_alloc_size is included for '0' at begin before '.' char and '.' char
		multiply_big_num_datas.result_alloc_size += 2;	
	}	
	multiply_big_num_datas.result_ptr = calloc(multiply_big_num_datas.result_alloc_size, sizeof(char));
	if(multiply_big_num_datas.proc_str1_ptr == NULL_DATA_PTR || multiply_big_num_datas.proc_str2_ptr == NULL_DATA_PTR || multiply_big_num_datas.result_ptr == NULL_DATA_PTR)
	{
		#ifdef TRACE_ERROR
		   printf("ERR: mul - memory address is NULL \n");
		#endif
		if(multiply_big_num_datas.proc_str1_ptr)
		{
			free(multiply_big_num_datas.proc_str1_ptr);			
		}
		if(multiply_big_num_datas.proc_str2_ptr)
		{
			free(multiply_big_num_datas.proc_str2_ptr);			
		}
		if(multiply_big_num_datas.result_ptr)
		{
			free(multiply_big_num_datas.result_ptr);			
		} 
		return NULL_DATA_PTR;
	}
	#ifdef TRACE_DATA
	   printf("TRA: mul - result alloc size = %u \n", multiply_big_num_datas.result_alloc_size);
	#endif
	if(i == 1)
	{
		multiply_big_num_datas.result_ptr[0] = '-';
	}
	/* grade-school method of multiplication */	
	for (proc_str1_ptr_pos = multiply_big_num_datas.proc_str1_len - 1; proc_str1_ptr_pos >= 0; proc_str1_ptr_pos--)
	{
		uint32_t carry = 0;
		
		result_ptr_init_pos = proc_str1_ptr_pos + multiply_big_num_datas.proc_str2_len;
		if(multiply_big_num_datas.result_ptr[0] == '-')
		{
			++result_ptr_init_pos;
		}			
		for (proc_str2_ptr_pos = multiply_big_num_datas.proc_str2_len - 1, result_ptr_pos = result_ptr_init_pos; proc_str2_ptr_pos >= 0; proc_str2_ptr_pos--, result_ptr_pos--)
		{
			uint32_t n = multiply_big_num_datas.proc_str1_ptr[proc_str1_ptr_pos] * multiply_big_num_datas.proc_str2_ptr[proc_str2_ptr_pos] + multiply_big_num_datas.result_ptr[result_ptr_pos] + carry;
			multiply_big_num_datas.result_ptr[result_ptr_pos] = (n % 10);
			carry = n / 10;
			#ifdef TRACE_DATA
			   printf("TRA: mul - str1[%d] = %u, str2[%d] = %u, result[%d] = %u, carry = %u \n", proc_str1_ptr_pos, multiply_big_num_datas.proc_str1_ptr[proc_str1_ptr_pos], 
			    proc_str2_ptr_pos,  multiply_big_num_datas.proc_str2_ptr[proc_str2_ptr_pos], result_ptr_pos, multiply_big_num_datas.result_ptr[result_ptr_pos], carry);
			#endif
		}
		multiply_big_num_datas.result_ptr[result_ptr_pos] += carry;
		#ifdef TRACE_DATA
		   printf("TRA: mul - result[%d] = %u, carry = %u \n", result_ptr_pos, multiply_big_num_datas.result_ptr[result_ptr_pos], carry);
		#endif   
	}
	if(multiply_big_num_datas.result_ptr[0] != '-')
	{
		result_ptr_init_pos = 0;
	}
	else
	{
		result_ptr_init_pos = 1;
	}	
    /* convert result from numeric into ASCII string numeric */
	for (result_ptr_pos = result_ptr_init_pos; result_ptr_pos < multiply_big_num_datas.proc_str1_len + multiply_big_num_datas.proc_str2_len + result_ptr_init_pos; ++result_ptr_pos)
	{	
		multiply_big_num_datas.result_ptr[result_ptr_pos] += '0';
	}
	#ifdef TRACE_DATA
	   printf("TRA: mul - result: %s before precision \n", multiply_big_num_datas.result_ptr);
	#endif
	if(multiply_big_num_datas.result_str_precision_digits != 0)
	{
		#ifdef TRACE_DATA
	    	printf("TRA: mul - result num precision width: %u \n", multiply_big_num_datas.result_str_precision_digits);
	    #endif		
		memmove(&multiply_big_num_datas.result_ptr[multiply_big_num_datas.proc_str1_len + multiply_big_num_datas.proc_str2_len + result_ptr_init_pos - multiply_big_num_datas.result_str_precision_digits + 1], 
		  &multiply_big_num_datas.result_ptr[multiply_big_num_datas.proc_str1_len + multiply_big_num_datas.proc_str2_len + result_ptr_init_pos - multiply_big_num_datas.result_str_precision_digits], 
		   multiply_big_num_datas.result_str_precision_digits);
	    multiply_big_num_datas.result_ptr[multiply_big_num_datas.proc_str1_len + multiply_big_num_datas.proc_str2_len + result_ptr_init_pos - multiply_big_num_datas.result_str_precision_digits] = '.';
		multiply_big_num_datas.result_ptr[multiply_big_num_datas.result_alloc_size - 1] = NULL_CHAR;		
	}
	#ifdef TRACE_DATA
	      printf("TRA: mul - result: %s before removing leading 0 \n", multiply_big_num_datas.result_ptr);
    #endif	
	while(multiply_big_num_datas.result_ptr[result_ptr_init_pos] == '0' && multiply_big_num_datas.result_ptr[result_ptr_init_pos + 1] != '.')
	{
	    memmove(&multiply_big_num_datas.result_ptr[result_ptr_init_pos], &multiply_big_num_datas.result_ptr[result_ptr_init_pos + 1], multiply_big_num_datas.result_alloc_size - 1);
	}
	if(multiply_big_num_datas.result_ptr[result_ptr_init_pos] == '.')
	{
		memmove(multiply_big_num_datas.result_ptr + result_ptr_init_pos + 1, multiply_big_num_datas.result_ptr + result_ptr_init_pos, multiply_big_num_datas.result_alloc_size);
	    multiply_big_num_datas.result_ptr[result_ptr_init_pos] = '0';
	}
	if(multiply_big_num_datas.proc_str1_ptr)
	{
	    free(multiply_big_num_datas.proc_str1_ptr); 	   
	}
	if(multiply_big_num_datas.proc_str2_ptr)
	{
	   free(multiply_big_num_datas.proc_str2_ptr);	   
	}
	#ifdef TRACE_INFO
	   printf("TRA: In Big num, %s * %s = %s \n", mul_str1, mul_str2, multiply_big_num_datas.result_ptr);
	#endif	
	return multiply_big_num_datas.result_ptr;    
}

/*------------------------------------------------------------*
FUNCTION NAME  : Big_Nums_Division

DESCRIPTION    :  
								
INPUT          : 

OUTPUT         : 

NOTE           :  Caller is responsible for freeing result memory.                  

Func ID        : 01.04  

BUGS           :              
-*------------------------------------------------------------*/ 
char *Big_Nums_Division(const char *const dividend_str1, const char *const divisor_str2, const uint8_t num_precision_digits)
{
	big_num_datas_t division_big_num_datas;
	char *str1 = NULL_DATA_PTR, *str2 = NULL_DATA_PTR, *temp_result = NULL_DATA_PTR, *temp_result2 = NULL_DATA_PTR, digit_str[2];
	int16_t proc_str_ptr_pos = 0, i, temp, temp2, cmp_result, result_ptr_pos = 0;
	uint8_t result_max_digits, result_ptr_init_pos = 0;
	
	#ifdef TRACE_FLOW
	   printf("TRA: In Big num, %s / %s \n", dividend_str1, divisor_str2);
	#endif
	division_big_num_datas.operand_str1 = dividend_str1;
	division_big_num_datas.operand_str2 = divisor_str2;
	if((Validate_Big_Num_Data(BIG_NUMS_DIVISION_OPER, num_precision_digits, &division_big_num_datas)) != SUCCESS)
    {
		return NULL_DATA_PTR; 
	}
	if(division_big_num_datas.result_ptr != NULL_DATA_PTR)
	{
		return division_big_num_datas.result_ptr;
	}
	if(division_big_num_datas.proc_str1_ptr == NULL_DATA_PTR || division_big_num_datas.proc_str2_ptr == NULL_DATA_PTR)
	{
		#ifdef TRACE_ERROR
		   printf("ERR: div - memory address is NULL \n");
		#endif
		if(division_big_num_datas.proc_str1_ptr != NULL_DATA_PTR)
		{
		    free(division_big_num_datas.proc_str1_ptr); 		  
		}
		if(division_big_num_datas.proc_str2_ptr != NULL_DATA_PTR)
		{
	        free(division_big_num_datas.proc_str2_ptr);			
		}
		return NULL_DATA_PTR;
	}
	temp = (division_big_num_datas.proc_str1_len - division_big_num_datas.proc_str1_precision_digits);
	temp2 = (division_big_num_datas.proc_str2_len - division_big_num_datas.proc_str2_precision_digits);
	i = (temp > temp2) ? temp : temp2;         
	if(i == temp2)	
	{
		//max num interger part digits is divisor, so quotient will be 0.<fraction part of quotient>
        if(temp == temp2)
		{	
            i = 0; 	
            if(division_big_num_datas.proc_str1_ptr[0] >= division_big_num_datas.proc_str2_ptr[0])
			{				
		       ++i;
			}
		}
		else
		{
			i = temp - temp2 + 1;
			if(division_big_num_datas.proc_str1_ptr[0] < division_big_num_datas.proc_str2_ptr[0])
			{
				--i;
			}
		}
	}
	else
	{
		i = temp - temp2;
		if(division_big_num_datas.proc_str1_ptr[0] >= division_big_num_datas.proc_str2_ptr[0])
		{
		    ++i;
		}		
	}
    result_max_digits = i + num_precision_digits;
	if(result_max_digits <= 0)
	{
		#ifdef TRACE_INFO
		   printf("TRA: div - result max digits <= 0 \n");
		#endif
		//alloc for 0 char is included before . char and included for .char 
		division_big_num_datas.result_alloc_size = num_precision_digits + 1 + 1 + 1;
		if((dividend_str1[0] == '-' && divisor_str2[0] != '-') || (dividend_str1[0] != '-' && divisor_str2[0] == '-'))
	    {
		    //result is negative, include alloc for sign '-' char at begin of result
		    result_ptr_init_pos = 1;
		    ++division_big_num_datas.result_alloc_size;
	    }
		division_big_num_datas.result_ptr = calloc(division_big_num_datas.result_alloc_size, sizeof(char));
		if(division_big_num_datas.result_ptr == NULL_DATA_PTR)
		{
			#ifdef TRACE_ERROR
		       printf("ERR: div - memory alloc failed \n");
		    #endif
			temp2 = 1;
	    	goto div_end_proc;
		}
		if(result_ptr_init_pos == 1)
		{
	    	division_big_num_datas.result_ptr[0] = '-';			
		}
		for(result_ptr_pos = result_ptr_init_pos; result_ptr_pos < num_precision_digits + 1 + 1 + result_ptr_init_pos; ++result_ptr_pos)
		{
			if(result_ptr_pos == result_ptr_init_pos + 1)
			{
				division_big_num_datas.result_ptr[result_ptr_pos] = '.';
				continue;
			}
			division_big_num_datas.result_ptr[result_ptr_pos] = '0';
		}
		division_big_num_datas.result_ptr[result_ptr_pos] = NULL_CHAR;
		temp2 = 0;
	    goto div_end_proc;
	}
	if(result_max_digits <= num_precision_digits)
	{
		//alloc for 0 char is included before . char and included for .char 
		division_big_num_datas.result_alloc_size = (num_precision_digits + 1 + 1 + 1);		
	}
	else
	{
	   //result alloc size include for '.' char 
	   division_big_num_datas.result_alloc_size = result_max_digits + 1 + 1;
	}	   
	if((dividend_str1[0] == '-' && divisor_str2[0] != '-') || (dividend_str1[0] != '-' && divisor_str2[0] == '-'))
	{
		//result is negative, include alloc for sign '-' char at begin of result
		result_ptr_init_pos = 1;
		++division_big_num_datas.result_alloc_size;
	}
	#ifdef TRACE_INFO
	   printf("TRA: div - result alloc size: %u \n", division_big_num_datas.result_alloc_size);
	#endif
	division_big_num_datas.result_ptr = calloc(division_big_num_datas.result_alloc_size, sizeof(char));
	str1 = calloc(division_big_num_datas.proc_str2_len + 1 + 1, sizeof(char)); 
	str2 = calloc(division_big_num_datas.proc_str2_len + 1 + 1, sizeof(char));
	if(str1 == NULL_DATA_PTR || str2 == NULL_DATA_PTR || division_big_num_datas.result_ptr == NULL_DATA_PTR)
	{
		#ifdef TRACE_ERROR
		   printf("ERR: div - memory alloc failed \n");
		#endif
		temp2 = 1;
		goto div_end_proc;
	}
	for(proc_str_ptr_pos = 0; proc_str_ptr_pos < division_big_num_datas.proc_str2_len; ++proc_str_ptr_pos)
	{
		if(proc_str_ptr_pos < division_big_num_datas.proc_str1_len)
		{
		    str1[proc_str_ptr_pos + 1] = division_big_num_datas.proc_str1_ptr[proc_str_ptr_pos] + '0';
		}
		else
		{
			str1[proc_str_ptr_pos + 1] = '0';
		}
		str2[proc_str_ptr_pos + 1] = division_big_num_datas.proc_str2_ptr[proc_str_ptr_pos] + '0';
	}
	str1[0] = '0';
	str2[0] = '0';
    result_ptr_pos = 0;
	i = 0;
	digit_str[1] = NULL_CHAR;
	cmp_result = 1;
	temp2 = 0;
	while(result_ptr_pos < result_max_digits)
	{
		temp = strcmp(str1, str2);
		#ifdef TRACE_INFO
		    printf("TRA: div - str1 = %s, str2 = %s, temp = %d \n",str1, str2, temp );
        #endif	
		if(temp == 0)
	    {
	    	division_big_num_datas.result_ptr[result_ptr_pos] = 1;
			#ifdef TRACE_INFO
			   printf("TRA: div - temp = 0, result[%d] = %u\n", result_ptr_pos, division_big_num_datas.result_ptr[result_ptr_pos] );
			#endif
			++result_ptr_pos;
	    }
        else if(temp > 0) 
		{
			 for(i = 1 ; i < 10; ++i)
			 {
				digit_str[0] = i + '0';	
               	temp_result2 = Big_Nums_Multiply(str2, digit_str);
                if(temp_result2 == NULL_DATA_PTR)
				{
					#ifdef TRACE_ERROR
					     printf("ERR: div - multiplicaton result failed \n");
					#endif
					temp2 = 1;
					goto div_end_proc;					
				}					
				if(strlen(temp_result2) <= division_big_num_datas.proc_str2_len)
				{
					temp_result = calloc(division_big_num_datas.proc_str2_len + 1 + 1,sizeof(char));
					if(temp_result == NULL_DATA_PTR)
					{
						#ifdef TRACE_ERROR
					       printf("ERR: div - memory allocation failed \n");
					    #endif
						temp2 = 1;
					    goto div_end_proc;
					}	
					memcpy(temp_result + 1, temp_result2, division_big_num_datas.proc_str2_len + 1);
					temp_result[0] = '0';					
					free(temp_result2);
					temp_result2 = NULL_DATA_PTR;
					temp_result2 = temp_result;
				}
				cmp_result = strcmp(str1, temp_result2);
                #ifdef TRACE_INFO
				   printf("TRA: temp > 0, str1 : %s, mul = %s, cmp = %d \n", str1, temp_result2, cmp_result);
                #endif
                if(i == 9 && cmp_result > 0)
				{
					temp_result = temp_result2;
					temp_result2 = NULL_DATA_PTR;
					cmp_result = -1;
                    i = 10;					
				}					
				if(cmp_result <= 0 )
				{
					if(cmp_result < 0)
					{
						division_big_num_datas.result_ptr[result_ptr_pos] = i - 1;						
						#ifdef TRACE_INFO
			               printf("TRA: cmp < 0, div - result[%d] = %u, ", result_ptr_pos, division_big_num_datas.result_ptr[result_ptr_pos]);
			            #endif
						 ++result_ptr_pos;
						if(i != 10)
						{
						   temp_result = Big_Nums_Subtract(temp_result2, str2);
						   free(temp_result2);
						   temp_result2 = NULL_DATA_PTR;
                           if(temp_result == NULL_DATA_PTR)
						   {
							   #ifdef TRACE_ERROR
							      printf("ERR: div - subtract result failed \n");
							   #endif
							    temp2 = 1;
					            goto div_end_proc;
						   }
						}
						else
						{
							i = 9;
							#ifdef TRACE_INFO
							  printf("TRA: str1 = %s, str2 = %s \n", str1, str2);
							#endif  
						}
					    memcpy(str2, temp_result, strlen(temp_result) + 1 );
						free(temp_result);	
						temp_result = NULL_DATA_PTR;
						temp_result = Big_Nums_Subtract(str1, str2);
                        if(temp_result == NULL_DATA_PTR)
						{
						    #ifdef TRACE_ERROR
							     printf("ERR: div - subtract result failed \n");
							#endif  
							temp2 = 1;
					        goto div_end_proc;
						}						
						memcpy(str1, temp_result, strlen(temp_result) + 1);
			            free(temp_result);
						temp_result = NULL_DATA_PTR;
                        str2[division_big_num_datas.proc_str2_len + 1 + 1] = NULL_CHAR;
		                for(i = division_big_num_datas.proc_str2_len;  i > 0 ; --i)
	                    {
	                      str2[i] = division_big_num_datas.proc_str2_ptr[i - 1] + '0';
	                    }
                        str2[0] = '0'; 						
					}
					else
					{
						division_big_num_datas.result_ptr[result_ptr_pos] = i;						
						#ifdef TRACE_INFO
			               printf("TRA: div - cmp = 0, result[%d] = %u, ", result_ptr_pos, division_big_num_datas.result_ptr[result_ptr_pos]);
			            #endif
						++result_ptr_pos;
						free(temp_result2);
					}
					break;
				}
				free(temp_result2);
			}
			if(i >= 10)
			{
				#ifdef TRACE_ERROR
				     printf("ERR: Mul digits >= 10 \n");
				#endif
				temp2 = 1;
				goto div_end_proc;
			}			
		}
		if(temp <= 0 || cmp_result <= 0)
		{
			#ifdef TRACE_INFO
			   printf("TRA: div - temp = %d, cmp = %d \n", temp, cmp_result);
			#endif
			if(cmp_result < 0)
			{
				i = strlen(str1);
				if(i < division_big_num_datas.proc_str2_len)
				{
				    temp2 = 0;
				}
				else
				{
					temp2 = 1;
				}
			}
			else if(temp < 0)
			{
				i = strlen(str1) - 1;
				memmove(str1, str1 + 1, strlen(str1) - 1);
				temp2 = 1; 				
			}
			else
			{
				i = 0;
				temp2 = 0;				
			}
		    for(; i < division_big_num_datas.proc_str2_len + temp2; ++i, ++proc_str_ptr_pos)
			{
			   if((proc_str_ptr_pos) < division_big_num_datas.proc_str1_len)
		       {
		              str1[i] = division_big_num_datas.proc_str1_ptr[proc_str_ptr_pos] + '0';
			    	  #if defined TRACE_INFO 
				           printf("TRA: data1[%d] = %u, ", proc_str_ptr_pos, division_big_num_datas.proc_str1_ptr[proc_str_ptr_pos]);
				      #endif
		       }
		       else
		       {
		             str1[i] = '0';
				     #if defined TRACE_INFO 
				         printf("TRA: pos = %d, ", proc_str_ptr_pos);
				     #endif 
			   }
			   if(i < (division_big_num_datas.proc_str2_len + temp2 - 1))
			   {
				   division_big_num_datas.result_ptr[result_ptr_pos] = 0;
			       #ifdef TRACE_INFO
			            printf("div - i = %u, result[%d] = %u \n", i, result_ptr_pos, division_big_num_datas.result_ptr[result_ptr_pos]);
			       #endif
			       ++result_ptr_pos;
			   }
		    }
		    str1[i] = NULL_CHAR;
			if(strlen(str1) <= division_big_num_datas.proc_str2_len)
		    {
			    memmove(str1 + 1, str1, division_big_num_datas.proc_str2_len + 1);
			    str1[0] = '0';
		    }
			#ifdef TRACE
			   printf("TRA: temp <= 0  or cmp <= 0, str1 : %s \n", str1); 
			#endif
			if(cmp_result < 0 || temp < 0)
			{
		        temp = strcmp(str1, str2);
				if(temp < 0)
				{
				    division_big_num_datas.result_ptr[result_ptr_pos] = 0;
			        #ifdef TRACE_INFO
			           printf("div - temp < 0, i = %u, result[%d] = %u \n", i, result_ptr_pos, division_big_num_datas.result_ptr[result_ptr_pos]);
			        #endif
			        ++result_ptr_pos;
			   }
			}					
			cmp_result = 1;
		}
	}
	temp2 = 0;
	for (result_ptr_pos = 0; result_ptr_pos < result_max_digits; ++result_ptr_pos)
	{	
		division_big_num_datas.result_ptr[result_ptr_pos] += '0';
	}
    #ifdef TRACE_INFO
	    printf("TRA: div - result : %s before add precision char \n", division_big_num_datas.result_ptr);
    #endif	
    if(result_max_digits <= num_precision_digits)
	{
		for(i = num_precision_digits - result_max_digits; i >= 0; --i)
		{
		   memmove(division_big_num_datas.result_ptr + 1, division_big_num_datas.result_ptr, strlen(division_big_num_datas.result_ptr) + 1);
		   division_big_num_datas.result_ptr[0] = '0';
		}
		result_max_digits = num_precision_digits + 1;
	}
	if(result_ptr_init_pos == 1)
	{
		memmove(division_big_num_datas.result_ptr + 1, division_big_num_datas.result_ptr, num_precision_digits + 1);
		division_big_num_datas.result_ptr[0] = '-';
	}
	memmove(division_big_num_datas.result_ptr + result_max_digits - num_precision_digits + result_ptr_init_pos + 1, 
	   division_big_num_datas.result_ptr + result_max_digits - num_precision_digits + result_ptr_init_pos, num_precision_digits + 1);
	division_big_num_datas.result_ptr[result_max_digits - num_precision_digits + result_ptr_init_pos] = '.';
    #ifdef TRACE_INFO
	    printf("TRA: div - result : %s, result_prec: %u before removing 0 \n", division_big_num_datas.result_ptr, num_precision_digits);
    #endif	
div_end_proc :	
	if(str1)
	{
	   	free(str1);			
	}
	if(str2)
	{
	   	free(str2);
	}
	if(division_big_num_datas.proc_str1_ptr)
	{
	  	free(division_big_num_datas.proc_str1_ptr);
	}
	if(division_big_num_datas.proc_str2_ptr)
	{
	      free(division_big_num_datas.proc_str2_ptr);
	}
	if(temp2 == 1)
	{
	   if(division_big_num_datas.result_ptr)
	   {
	        free(division_big_num_datas.result_ptr);
	   }
	   return NULL_DATA_PTR;
	}
	#ifdef TRACE_INFO
	   printf("TRA: In Big num, %s / %s = %s \n", dividend_str1, divisor_str2, division_big_num_datas.result_ptr);
	#endif				
    return division_big_num_datas.result_ptr; 
}

/*------------------------------------------------------------*
FUNCTION NAME  : Big_Nums_Modulus

DESCRIPTION    :  
								
INPUT          : 

OUTPUT         : 

NOTE           :  Caller is responsible for freeing result memory.                  

Func ID        : 01.04  

BUGS           :              
-*------------------------------------------------------------*/ 
char *Big_Nums_Modulus(const char *const dividend_str1, const char *const divisor_str2)
{
	big_num_datas_t modulus_big_num_datas;
	char *str1 = NULL_DATA_PTR, *str2 = NULL_DATA_PTR, *temp_result = NULL_DATA_PTR, *temp_result2 = NULL_DATA_PTR, digit_str[2];
	int16_t proc_str1_ptr_pos = 0, i, temp, temp2, cmp_result, result_ptr_pos = 0;
	uint8_t result_ptr_init_pos = 0, str_cmp_flag = 0;
	
	#ifdef TRACE_FLOW
	   printf("TRA: In Big num, %s %% %s \n", dividend_str1, divisor_str2);
	#endif
	modulus_big_num_datas.operand_str1 = dividend_str1;
	modulus_big_num_datas.operand_str2 = divisor_str2;
	if((Validate_Big_Num_Data(BIG_NUMS_MODULUS_OPER, RESULT_BASED_PRECISION_DIGITS, &modulus_big_num_datas)) != SUCCESS)
    {
		return NULL_DATA_PTR; 
	}
	if(modulus_big_num_datas.result_ptr != NULL_DATA_PTR)
	{
		return modulus_big_num_datas.result_ptr;
	}
	if(modulus_big_num_datas.proc_str1_ptr == NULL_DATA_PTR || modulus_big_num_datas.proc_str2_ptr == NULL_DATA_PTR)
	{
		#ifdef TRACE_ERROR
		   printf("ERR: mod - memory address is NULL \n");
		#endif
		if(modulus_big_num_datas.proc_str1_ptr != NULL_DATA_PTR)
		{
		    free(modulus_big_num_datas.proc_str1_ptr); 		  
		}
		if(modulus_big_num_datas.proc_str2_ptr != NULL_DATA_PTR)
		{
	        free(modulus_big_num_datas.proc_str2_ptr);			
		}
		return NULL_DATA_PTR;
	}
	if(modulus_big_num_datas.operand_str1[0] == '-')
	{
		result_ptr_init_pos = 1;
		++modulus_big_num_datas.result_alloc_size;
	}
	if(modulus_big_num_datas.proc_str1_len < modulus_big_num_datas.proc_str2_len)
	{
		modulus_big_num_datas.result_alloc_size += (modulus_big_num_datas.proc_str1_len + 1);
		modulus_big_num_datas.result_ptr = calloc(modulus_big_num_datas.result_alloc_size, sizeof(char));
		if(modulus_big_num_datas.result_ptr == NULL_DATA_PTR)
		{
		  	#ifdef TRACE_ERROR
		        printf("ERR: mod - memory address is NULL \n");
		    #endif
		    if(modulus_big_num_datas.proc_str1_ptr != NULL_DATA_PTR)
	     	{
		       free(modulus_big_num_datas.proc_str1_ptr); 		  
	    	}
		    if(modulus_big_num_datas.proc_str2_ptr != NULL_DATA_PTR)
		    { 
	           free(modulus_big_num_datas.proc_str2_ptr);			
	    	}
		    return NULL_DATA_PTR; 	
		}
		for(result_ptr_pos = result_ptr_init_pos; result_ptr_pos < modulus_big_num_datas.proc_str1_len + result_ptr_init_pos; ++result_ptr_pos)
		{
			modulus_big_num_datas.result_ptr[result_ptr_pos] = modulus_big_num_datas.proc_str1_ptr[result_ptr_pos - result_ptr_init_pos] + '0';
		}
        if(result_ptr_init_pos == 1)
		{
			modulus_big_num_datas.result_ptr[0] = '-';
		}
        if(modulus_big_num_datas.proc_str1_ptr != NULL_DATA_PTR)
	   	{
		      free(modulus_big_num_datas.proc_str1_ptr); 		  
	    }
		if(modulus_big_num_datas.proc_str2_ptr != NULL_DATA_PTR)
		{ 
	        free(modulus_big_num_datas.proc_str2_ptr);			
	    }
        return  modulus_big_num_datas.result_ptr;		
	}
	modulus_big_num_datas.result_alloc_size += (modulus_big_num_datas.proc_str2_len + 2);
	#ifdef TRACE_INFO
	   printf("TRA: mod - result alloc size: %u \n", modulus_big_num_datas.result_alloc_size);
	#endif
	modulus_big_num_datas.result_ptr = calloc(modulus_big_num_datas.result_alloc_size, sizeof(char));
	str1 = calloc(modulus_big_num_datas.proc_str2_len + 1 + 1, sizeof(char)); 
	str2 = calloc(modulus_big_num_datas.proc_str2_len + 1 + 1, sizeof(char));
	if(str1 == NULL_DATA_PTR || str2 == NULL_DATA_PTR || modulus_big_num_datas.result_ptr == NULL_DATA_PTR)
	{
		#ifdef TRACE_ERROR
		   printf("ERR: mod - memory alloc failed \n");
		#endif
		temp2 = 1;
		goto mod_end_proc;
	}
	for(proc_str1_ptr_pos = 0; proc_str1_ptr_pos < modulus_big_num_datas.proc_str2_len; ++proc_str1_ptr_pos)
	{
		str2[proc_str1_ptr_pos + 1] = modulus_big_num_datas.proc_str2_ptr[proc_str1_ptr_pos] + '0';
	}
	str1[0] = '0';
	str2[0] = '0';
	i = 0;
	digit_str[1] = NULL_CHAR;
	proc_str1_ptr_pos = 0;
	cmp_result = 1;
	temp2 = 0;
    temp = 0;
	str_cmp_flag = 0;
	if(modulus_big_num_datas.proc_str1_len == modulus_big_num_datas.proc_str2_len)
	{
		str_cmp_flag = 1;
	}
	while(proc_str1_ptr_pos <= modulus_big_num_datas.proc_str1_len + str_cmp_flag)
	{
		temp = strcmp(str1, str2);
		#ifdef TRACE_INFO
		    printf("TRA: mod - str1 = %s, str2 = %s, temp = %d \n",str1, str2, temp );
        #endif
		if(temp > 0) 
		{
			 for(i = 1 ; i < 10; ++i)
			 {
				digit_str[0] = i + '0';	
               	temp_result2 = Big_Nums_Multiply(str2, digit_str);
                if(temp_result2 == NULL_DATA_PTR)
				{
					#ifdef TRACE_ERROR
					     printf("ERR: mod - multiplicaton result failed \n");
					#endif
					temp2 = 1;
					goto mod_end_proc;					
				}					
				if(strlen(temp_result2) <= modulus_big_num_datas.proc_str2_len)
				{
					temp_result = calloc(modulus_big_num_datas.proc_str2_len + 1 + 1,sizeof(char));
					if(temp_result == NULL_DATA_PTR)
					{
						#ifdef TRACE_ERROR
					       printf("ERR: mod - memory allocation failed \n");
					    #endif
						temp2 = 1;
					    goto mod_end_proc;
					}	
					memcpy(temp_result + 1, temp_result2, modulus_big_num_datas.proc_str2_len + 1);
					temp_result[0] = '0';					
					free(temp_result2);
					temp_result2 = NULL_DATA_PTR;
					temp_result2 = temp_result;
				}
				cmp_result = strcmp(str1, temp_result2);
                #ifdef TRACE_INFO
				   printf("TRA: mod - temp > 0, str1 : %s, mul = %s, cmp = %d \n", str1, temp_result2, cmp_result);
                #endif
                if(i == 9 && cmp_result > 0)
				{
					temp_result = temp_result2;
					temp_result2 = NULL_DATA_PTR;
					cmp_result = -1;
                    i = 10;					
				}					
				if(cmp_result <= 0 )
				{
					if(cmp_result < 0)
					{
						if(i != 10)
						{
						   temp_result = Big_Nums_Subtract(temp_result2, str2);
						   free(temp_result2);
						   temp_result2 = NULL_DATA_PTR;
                           if(temp_result == NULL_DATA_PTR)
						   {
							   #ifdef TRACE_ERROR
							      printf("ERR: mod - subtract result failed \n");
							   #endif
							    temp2 = 1;
					            goto mod_end_proc;
						   }
						}
						else
						{
							i = 9;
							#ifdef TRACE_INFO
							  printf("TRA: mod - str1 = %s, str2 = %s \n", str1, str2);
							#endif  
						}
					    memcpy(str2, temp_result, strlen(temp_result) + 1 );
						free(temp_result);	
						temp_result = NULL_DATA_PTR;
						temp_result = Big_Nums_Subtract(str1, str2);
                        if(temp_result == NULL_DATA_PTR)
						{
						    #ifdef TRACE_ERROR
							     printf("ERR: mod - subtract result failed \n");
							#endif  
							temp2 = 1;
					        goto mod_end_proc;
						}
						memcpy(str1, temp_result, strlen(temp_result) + 1);
			            free(temp_result);
						temp_result = NULL_DATA_PTR;
                        str2[modulus_big_num_datas.proc_str2_len + 1 + 1] = NULL_CHAR;
		                for(i = modulus_big_num_datas.proc_str2_len;  i > 0 ; --i)
	                    {
	                      str2[i] = modulus_big_num_datas.proc_str2_ptr[i - 1] + '0';
	                    }
                        str2[0] = '0'; 						
					}
					else
					{
						free(temp_result2);
					}
					break;
				}
				free(temp_result2);
			}
			if(i >= 10)
			{
				#ifdef TRACE_ERROR
				     printf("ERR: mod - Mul digits >= 10 \n");
				#endif
				temp2 = 1;
				goto mod_end_proc;
			}			
		}
		if(temp <= 0 || cmp_result <= 0)
		{
			#ifdef TRACE_INFO
			   printf("TRA: mod - temp = %d, cmp = %d \n", temp, cmp_result);
			#endif
			if(cmp_result < 0)
			{
				i = strlen(str1);
				if(i < modulus_big_num_datas.proc_str2_len)
				{
				    temp2 = 0;
				}
				else
				{
					temp2 = 1;
				}
			}
			else if(temp < 0)
			{
				i = strlen(str1) - 1;
				memmove(str1, str1 + 1, strlen(str1) - 1);
				temp2 = 1; 				
			}
			else
			{
				i = 0;
				temp2 = 0;				
			}
		    for(; i < modulus_big_num_datas.proc_str2_len + temp2; ++i, ++proc_str1_ptr_pos)
			{
			   if((proc_str1_ptr_pos) < modulus_big_num_datas.proc_str1_len)
		       {
		           str1[i] = modulus_big_num_datas.proc_str1_ptr[proc_str1_ptr_pos] + '0';
			       #if defined TRACE_INFO 
				        printf("TRA: mod - data1[%d] = %u \n", proc_str1_ptr_pos, modulus_big_num_datas.proc_str1_ptr[proc_str1_ptr_pos]);
				   #endif
		       }
		       else
		       {
				   str1[i] = NULL_CHAR;
			   }
		    }
		    str1[i] = NULL_CHAR;
			if(strlen(str1) <= modulus_big_num_datas.proc_str2_len)
		    {
			    memmove(str1 + 1, str1, modulus_big_num_datas.proc_str2_len + 1);
			    str1[0] = '0';
		    }
			#ifdef TRACE
			   printf("TRA: mod - temp <= 0 or cmp <= 0, str1 : %s \n", str1); 
			#endif
			if(cmp_result < 0 || temp < 0)
			{
		        temp = strcmp(str1, str2);
			}					
			cmp_result = 1;
		}
	}
	for(proc_str1_ptr_pos = 0; proc_str1_ptr_pos < modulus_big_num_datas.proc_str1_len + 1; ++proc_str1_ptr_pos)
	{
		modulus_big_num_datas.result_ptr[proc_str1_ptr_pos]	= str1[proc_str1_ptr_pos]; 
	}
	modulus_big_num_datas.result_ptr[proc_str1_ptr_pos] = NULL_CHAR;
	if(result_ptr_init_pos == 1 && temp != 0)
	{
		modulus_big_num_datas.result_ptr[0] = '-';
	}
	while(modulus_big_num_datas.result_ptr[result_ptr_init_pos] == '0' && modulus_big_num_datas.result_ptr[result_ptr_init_pos + 1] != NULL_CHAR)
	{
	    memmove(&modulus_big_num_datas.result_ptr[result_ptr_init_pos], &modulus_big_num_datas.result_ptr[result_ptr_init_pos + 1], modulus_big_num_datas.result_alloc_size - 1);
	}
	temp2 = 0;		
mod_end_proc :	
	if(str1)
	{
	   	free(str1);			
	}
	if(str2)
	{
	   	free(str2);
	}
	if(modulus_big_num_datas.proc_str1_ptr)
	{
	  	free(modulus_big_num_datas.proc_str1_ptr);
	}
	if(modulus_big_num_datas.proc_str2_ptr)
	{
	      free(modulus_big_num_datas.proc_str2_ptr);
	}
	if(temp2 == 1)
	{
	   if(modulus_big_num_datas.result_ptr)
	   {
	        free(modulus_big_num_datas.result_ptr);
	   }
	   return NULL_DATA_PTR;
	}
	#ifdef TRACE_INFO
	   printf("TRA: In Big num, %s %% %s = %s \n", dividend_str1, divisor_str2, modulus_big_num_datas.result_ptr);
	#endif				
    return modulus_big_num_datas.result_ptr; 	
}

/*------------------------------------------------------------*
FUNCTION NAME  : Big_Nums_Sum

DESCRIPTION    :  find sum of two large numbers.
								
INPUT          : 

OUTPUT         : 

NOTE           : Caller is responsible for freeing result memory.                  

Func ID        : 01.04  

BUGS           :              
-*------------------------------------------------------------*/
char *Big_Nums_Sum(const char *const aug_str1, const char *const add_str2) 
{ 
    big_num_datas_t add_big_num_datas;
    char *result_ptr, *temp_ptr;
	int16_t proc_str1_ptr_pos = 0, proc_str2_ptr_pos = 0, result_ptr_pos = 0, i, diff_proc_str_len, carry = 0; 
	uint8_t result_ptr_init_pos, min_proc_str_len = 0, max_proc_str_len, diff_precision_digits = 0, min_precision_digits = 0;	
	
	#ifdef TRACE_FLOW
	   printf("TRA: In Big num, %s + %s \n", aug_str1, add_str2);
	#endif
	add_big_num_datas.operand_str1 = aug_str1;
	add_big_num_datas.operand_str2 = add_str2;
	if((Validate_Big_Num_Data(BIG_NUMS_SUM_OPER, RESULT_BASED_PRECISION_DIGITS, &add_big_num_datas)) != SUCCESS)
    {
		return NULL_DATA_PTR;
	}
	if(add_big_num_datas.result_ptr != NULL_DATA_PTR)
	{
		return add_big_num_datas.result_ptr;
	}
	if((aug_str1[0] != '-' && add_str2[0] == '-') || (aug_str1[0] == '-' && add_str2[0] != '-'))
	{
		if(add_big_num_datas.proc_str1_ptr)
		{
		   free(add_big_num_datas.proc_str1_ptr); 
		}
		if(add_big_num_datas.proc_str2_ptr)
		{
    	    free(add_big_num_datas.proc_str2_ptr);
		}
		i = 0;
		if(aug_str1[0] != '-' && add_str2[0] == '-')
		{
			#ifdef TRACE_DATA
			   printf("TRA: sum - result = '+' and '-' \n");
			#endif
			result_ptr = Big_Nums_Subtract(aug_str1, add_str2 + 1);	
		}
		else
		{
			#ifdef TRACE_DATA
			   printf("TRA: sum - result = '-' and '+' \n");
			#endif
			result_ptr = Big_Nums_Subtract(add_str2, aug_str1 + 1);
		}
		return result_ptr;
	}
	min_proc_str_len = (add_big_num_datas.proc_str1_len < add_big_num_datas.proc_str2_len) ? add_big_num_datas.proc_str1_len: add_big_num_datas.proc_str2_len;
	max_proc_str_len = (add_big_num_datas.proc_str1_len > add_big_num_datas.proc_str2_len) ? add_big_num_datas.proc_str1_len: add_big_num_datas.proc_str2_len;
	diff_precision_digits = min_precision_digits = 0;
	//result_alloc_size is included for sign char at begin of result_ptr and NULL_CHAR at end of result_ptr 
	add_big_num_datas.result_alloc_size = max_proc_str_len + 1 + 2;	
	if(aug_str1[0] == '+' && add_str2[0] == '+')
	{
		//result_alloc_size sign char is excluded
		--add_big_num_datas.result_alloc_size;
	}
	if(add_big_num_datas.proc_str1_ptr == NULL_DATA_PTR || add_big_num_datas.proc_str2_ptr == NULL_DATA_PTR)
	{
		#ifdef TRACE_ERROR
		   printf("ERR: sum - memory address is NULL \n");
		#endif
	    if(add_big_num_datas.proc_str1_ptr == NULL_DATA_PTR)
		{
			free(add_big_num_datas.proc_str1_ptr);
		}
		if(add_big_num_datas.proc_str2_ptr == NULL_DATA_PTR)
		{
			free(add_big_num_datas.proc_str2_ptr);
		}
		return NULL_DATA_PTR;
	}
	if(add_big_num_datas.proc_str1_precision_digits != 0 || add_big_num_datas.proc_str2_precision_digits != 0 )
	{
		min_precision_digits = (add_big_num_datas.proc_str1_precision_digits < add_big_num_datas.proc_str2_precision_digits) ? 
		   add_big_num_datas.proc_str1_precision_digits : add_big_num_datas.proc_str2_precision_digits; 
		add_big_num_datas.result_str_precision_digits = (add_big_num_datas.proc_str1_precision_digits > add_big_num_datas.proc_str2_precision_digits) ? 
		   add_big_num_datas.proc_str1_precision_digits : add_big_num_datas.proc_str2_precision_digits;
        diff_precision_digits = add_big_num_datas.result_str_precision_digits - min_precision_digits;
        #ifdef TRACE_DATA
		   printf("TRA: sum - min_prec_digits = %u, max_prec_digits = %u, diff_prec_digits = %u\n", min_precision_digits, add_big_num_datas.result_str_precision_digits, diff_precision_digits);
        #endif		
        if(min_precision_digits == add_big_num_datas.proc_str1_precision_digits)
		{
			temp_ptr = add_big_num_datas.proc_str1_ptr;
			add_big_num_datas.proc_str1_ptr = realloc(add_big_num_datas.proc_str1_ptr, add_big_num_datas.proc_str1_len + 1 + diff_precision_digits);
			if(add_big_num_datas.proc_str1_ptr == NULL_DATA_PTR)
			{
				#ifdef TRACE_ERROR
				   printf("ERR: sum - memory alloc failed \n"); 
				#endif 
				if(temp_ptr)
				{
					free(temp_ptr);
				}
				if(add_big_num_datas.proc_str2_ptr)
				{
					free(add_big_num_datas.proc_str2_ptr);
				}
				return NULL_DATA_PTR;
			}
			#ifdef TRACE_DATA
			   printf("TRA: sum - realloc str1 size : %u, ", add_big_num_datas.proc_str1_len);
			#endif
			for(i = 0; i < diff_precision_digits; ++i)
			{
				add_big_num_datas.proc_str1_ptr[add_big_num_datas.proc_str1_len + i] = 0;
			}
			add_big_num_datas.proc_str1_ptr[add_big_num_datas.proc_str1_len + i] = NULL_CHAR;
			add_big_num_datas.proc_str1_len += diff_precision_digits;			
		}
        else
		{
			temp_ptr = add_big_num_datas.proc_str2_ptr;
			add_big_num_datas.proc_str2_ptr = realloc(add_big_num_datas.proc_str2_ptr, add_big_num_datas.proc_str2_len + 1 + diff_precision_digits);
			if(add_big_num_datas.proc_str2_ptr == NULL_DATA_PTR)
			{
				#ifdef TRACE_ERROR
				   printf("ERR: sum - memory alloc failed \n"); 
				#endif 
				if(temp_ptr)
				{
					free(temp_ptr);
				}
				if(add_big_num_datas.proc_str1_ptr)
				{
					free(add_big_num_datas.proc_str1_ptr);
				}
				return NULL_DATA_PTR;
			}
			for(i = 0; i < diff_precision_digits; ++i)
			{
				add_big_num_datas.proc_str2_ptr[add_big_num_datas.proc_str2_len + i] = 0;
			}
			add_big_num_datas.proc_str2_ptr[add_big_num_datas.proc_str2_len + i] = NULL_CHAR;
			add_big_num_datas.proc_str2_len += diff_precision_digits;
			#ifdef TRACE_DATA
			   printf("TRA: sum - realloc str2 size : %u, ", add_big_num_datas.proc_str2_len);
			#endif
		}		
		min_proc_str_len = (add_big_num_datas.proc_str1_len < add_big_num_datas.proc_str2_len) ? add_big_num_datas.proc_str1_len: add_big_num_datas.proc_str2_len;
	    max_proc_str_len = (add_big_num_datas.proc_str1_len > add_big_num_datas.proc_str2_len) ? add_big_num_datas.proc_str1_len: add_big_num_datas.proc_str2_len;
		++add_big_num_datas.result_alloc_size;
	}
	#ifdef TRACE_DATA
	   printf("sum - result alloc size = %u \n", add_big_num_datas.result_alloc_size);
	#endif
	add_big_num_datas.result_ptr = calloc(add_big_num_datas.result_alloc_size, sizeof(char));
	if(add_big_num_datas.result_ptr == NULL_DATA_PTR)
	{
		#ifdef TRACE_ERROR
		   printf("ERR: sum - memory alloc failed \n"); 
		#endif 
		if(add_big_num_datas.proc_str1_ptr)
		{
			free(add_big_num_datas.proc_str1_ptr);
		}
		if(add_big_num_datas.proc_str2_ptr)
		{
			free(add_big_num_datas.proc_str2_ptr);
		}
		return NULL_DATA_PTR;
	}
	diff_proc_str_len = add_big_num_datas.proc_str1_len - add_big_num_datas.proc_str2_len;
	if(diff_proc_str_len < 0)
	{
		diff_proc_str_len = -diff_proc_str_len;		
	}
	#ifdef TRACE_DATA
	   printf("TRA: sum - min_str_len = %u, max_str_len = %u, max_min_len_diff = %u \n", min_proc_str_len, max_proc_str_len, diff_proc_str_len);
	#endif
	
	/* grade-school method of addition */
	carry = 0;
	for(i = min_proc_str_len - 1, result_ptr_pos = max_proc_str_len; i >= 0 ; --i, --result_ptr_pos)
	{
		int16_t sum;
        
        if(min_proc_str_len == add_big_num_datas.proc_str1_len)
		{
			sum = add_big_num_datas.proc_str1_ptr[i] + add_big_num_datas.proc_str2_ptr[i + diff_proc_str_len] + carry;
			#ifdef TRACE_DATA
			   printf("TRA: sum - str1[%d] = %u, str2[%d] = %u, carry = %d, ", i, add_big_num_datas.proc_str1_ptr[i], i + diff_proc_str_len, 
			     add_big_num_datas.proc_str2_ptr[i + diff_proc_str_len], carry);
			#endif
		}
        else
		{ 
	        sum = add_big_num_datas.proc_str1_ptr[i + diff_proc_str_len] + add_big_num_datas.proc_str2_ptr[i] + carry;
			#ifdef TRACE_DATA
			   printf("TRA: sum - str1[%d] = %u, str2[%d] = %u, carry = %d, ", i + diff_proc_str_len, add_big_num_datas.proc_str1_ptr[i + diff_proc_str_len],
    			   i, add_big_num_datas.proc_str2_ptr[i], carry);
			#endif
		}
        add_big_num_datas.result_ptr[result_ptr_pos] = (sum % 10);
		#ifdef TRACE_DATA
		   printf("result[%d] = %u \n", result_ptr_pos, add_big_num_datas.result_ptr[result_ptr_pos]);
		#endif
        carry = sum / 10; 		
	}
	// Add remaining digits  
    for (i= diff_proc_str_len - 1; i >= 0; --i, --result_ptr_pos) 
    { 
        int16_t sum;
		
		if(min_proc_str_len == add_big_num_datas.proc_str1_len)
		{
			sum = ((add_big_num_datas.proc_str2_ptr[i]) + carry); 
			#ifdef TRACE_DATA
			   printf("TRA: sum - str2[%d] = %u, carry = %d, ", i, add_big_num_datas.proc_str2_ptr[i], carry);
			#endif
		}
		else
		{
			sum = ((add_big_num_datas.proc_str1_ptr[i]) + carry); 
			#ifdef TRACE_DATA
			   printf("TRA: sum - str1[%d] = %u, carry = %d, ", i, add_big_num_datas.proc_str1_ptr[i], carry);
			#endif
		}
        add_big_num_datas.result_ptr[result_ptr_pos] = (sum % 10);
		#ifdef TRACE_DATA
		    printf("result[%d] = %u \n", result_ptr_pos, add_big_num_datas.result_ptr[result_ptr_pos]);
		#endif
        carry = sum / 10; 
    }   
    // Add remaining carry 
    add_big_num_datas.result_ptr[result_ptr_pos] = carry;
	#ifdef TRACE_DATA
		printf("TRA: sum -  At end, result[%d] = %u, carry = %d \n", result_ptr_pos, add_big_num_datas.result_ptr[result_ptr_pos], carry);
	#endif
	if(aug_str1[0] == '-' && add_str2[0] == '-')
	{
	    result_ptr_init_pos = 1;
	}
	else
	{
		result_ptr_init_pos = 0;
	}
	if(result_ptr_init_pos == 1)
	{
		memmove(add_big_num_datas.result_ptr + 1, add_big_num_datas.result_ptr, max_proc_str_len + 1 + 2);
		add_big_num_datas.result_ptr[0] = '-';
	}
	/* convert result from numeric into ASCII string numeric */
	for (result_ptr_pos = result_ptr_init_pos; result_ptr_pos < max_proc_str_len + 1 + result_ptr_init_pos; ++result_ptr_pos)
	{	
		add_big_num_datas.result_ptr[result_ptr_pos] += '0';
	}
	add_big_num_datas.result_ptr[result_ptr_pos] = NULL_CHAR;
	#ifdef TRACE_DATA
	   printf("TRA: sum - result: %s before precision \n", add_big_num_datas.result_ptr);
	#endif
	if(add_big_num_datas.result_str_precision_digits != 0)
	{
		#ifdef TRACE_DATA
	    	printf("TRA: sum - result num precision width: %u \n", add_big_num_datas.result_str_precision_digits);
	    #endif		
		memmove(&add_big_num_datas.result_ptr[max_proc_str_len + 1 + result_ptr_init_pos - add_big_num_datas.result_str_precision_digits + 1], 
		  &add_big_num_datas.result_ptr[max_proc_str_len + 1 + result_ptr_init_pos - add_big_num_datas.result_str_precision_digits], add_big_num_datas.result_str_precision_digits);
	    add_big_num_datas.result_ptr[max_proc_str_len + 1 + result_ptr_init_pos - add_big_num_datas.result_str_precision_digits] = '.';
		add_big_num_datas.result_ptr[add_big_num_datas.result_alloc_size - 1] = NULL_CHAR;		
	}
	#ifdef TRACE_DATA
	     printf("TRA: sum - result: %s before removing leading 0 \n", add_big_num_datas.result_ptr);
    #endif	
	while(add_big_num_datas.result_ptr[result_ptr_init_pos] == '0' && add_big_num_datas.result_ptr[result_ptr_init_pos + 1] != '.')
	{
	    memmove(&add_big_num_datas.result_ptr[result_ptr_init_pos], &add_big_num_datas.result_ptr[result_ptr_init_pos + 1], add_big_num_datas.result_alloc_size - 1);
	}
	free(add_big_num_datas.proc_str1_ptr); 
	free(add_big_num_datas.proc_str2_ptr);
	#ifdef TRACE_INFO
	   printf("TRA: In Big num, %s + %s = %s\n", aug_str1, add_str2, add_big_num_datas.result_ptr);
	#endif
	return  add_big_num_datas.result_ptr;	
} 

/*------------------------------------------------------------*
FUNCTION NAME  : Big_Nums_Subtract

DESCRIPTION    :  find sum of two large numbers.
								
INPUT          : 

OUTPUT         : 

NOTE           : Caller is responsible for freeing result memory.                  

Func ID        : 01.04  

BUGS           :              
-*------------------------------------------------------------*/
char *Big_Nums_Subtract(const char *const min_str1, const char *const subt_str2) 
{ 
    big_num_datas_t subtract_big_num_datas;
	char *result_ptr, *temp_str2_ptr;
	int16_t proc_str1_ptr_pos = 0, proc_str2_ptr_pos = 0, result_ptr_pos = 0, i, diff_proc_str_len, carry = 0, subtract; 
	uint8_t result_ptr_init_pos, min_proc_str_len = 0, max_proc_str_len, diff_precision_digits = 0, min_precision_digits = 0, zero_subt_str2_carry;	
	
    #ifdef TRACE_FLOW
	    printf("TRA: In Big num, %s - %s \n", min_str1, subt_str2);
    #endif	
	subtract_big_num_datas.operand_str1 = min_str1;
	subtract_big_num_datas.operand_str2 = subt_str2;
	if((Validate_Big_Num_Data(BIG_NUMS_SUBTRACT_OPER, RESULT_BASED_PRECISION_DIGITS, &subtract_big_num_datas)) != SUCCESS)
    {
		return NULL_DATA_PTR;
	}
	if(subtract_big_num_datas.result_ptr != NULL_DATA_PTR)
	{
		return subtract_big_num_datas.result_ptr;
	}
	if(subtract_big_num_datas.proc_str1_ptr == NULL_DATA_PTR || subtract_big_num_datas.proc_str2_ptr == NULL_DATA_PTR)
	{
		#ifdef TRACE_ERROR
			   printf("ERR: diff - memory is NULL \n");
		#endif
		if(subtract_big_num_datas.proc_str1_ptr)
		{
			free(subtract_big_num_datas.proc_str1_ptr);
		}
		if(subtract_big_num_datas.proc_str2_ptr)
		{
			free(subtract_big_num_datas.proc_str2_ptr);
		}
		return NULL_DATA_PTR;
	}
	if((min_str1[0] == '-' && subt_str2[0] != '-') || (min_str1[0] != '-' && subt_str2[0] == '-'))
	{
		temp_str2_ptr = calloc(subtract_big_num_datas.proc_str2_len + 2, sizeof(char));
		if(temp_str2_ptr == NULL_DATA_PTR)
		{
			#ifdef TRACE_ERROR
			   printf("ERR: diff - memory alloc failed \n");
			#endif
			if(subtract_big_num_datas.proc_str1_ptr)
			{
				free(subtract_big_num_datas.proc_str1_ptr);
			}
			if(subtract_big_num_datas.proc_str2_ptr)
			{
				free(subtract_big_num_datas.proc_str2_ptr);
			}
			return NULL_DATA_PTR;
		}
		i = 0;
		if(subt_str2[0] == '-' || subt_str2[0] == '+')
		{
			i = 1;
		}
		memcpy(temp_str2_ptr + 1, subt_str2 + i, strlen(subt_str2 + i) + 1);		
		if(min_str1[0] == '-' && subt_str2[0] != '-')
		{
			temp_str2_ptr[0] = '-';
		}
		else
		{		            
			temp_str2_ptr[0] = '+';			
		}
		#ifdef TRACE_DATA
		   printf("TRA: Sum oper, addand = %s \n", temp_str2_ptr);
		#endif
		free(subtract_big_num_datas.proc_str1_ptr); 
	    free(subtract_big_num_datas.proc_str2_ptr);
		result_ptr = Big_Nums_Sum(min_str1, temp_str2_ptr);
		free(temp_str2_ptr);
		return result_ptr;
	}
	if(min_str1[0] == '-' && subt_str2[0] == '-')
	{
		free(subtract_big_num_datas.proc_str1_ptr); 
	    free(subtract_big_num_datas.proc_str2_ptr);
        result_ptr = Big_Nums_Subtract(subt_str2 + 1, min_str1 + 1); 
        return result_ptr;	
	}
	min_proc_str_len = (subtract_big_num_datas.proc_str1_len < subtract_big_num_datas.proc_str2_len) ? subtract_big_num_datas.proc_str1_len: subtract_big_num_datas.proc_str2_len;
	max_proc_str_len = (subtract_big_num_datas.proc_str1_len > subtract_big_num_datas.proc_str2_len) ? subtract_big_num_datas.proc_str1_len: subtract_big_num_datas.proc_str2_len;
	#ifdef TRACE_DATA
	   printf("TRA: diff - min_str_len : %u, max_str_len = %u \n", min_proc_str_len, max_proc_str_len);
	#endif
	diff_precision_digits = min_precision_digits = 0;
	//result_alloc_size is included for sign char at begin of result_ptr and NULL_CHAR at end of result_ptr 
	subtract_big_num_datas.result_alloc_size = max_proc_str_len + 2;	
	if(subtract_big_num_datas.proc_str1_precision_digits != 0 || subtract_big_num_datas.proc_str2_precision_digits != 0 )
	{
		min_precision_digits = (subtract_big_num_datas.proc_str1_precision_digits < subtract_big_num_datas.proc_str2_precision_digits) ? 
		   subtract_big_num_datas.proc_str1_precision_digits : subtract_big_num_datas.proc_str2_precision_digits; 
		subtract_big_num_datas.result_str_precision_digits = (subtract_big_num_datas.proc_str1_precision_digits > subtract_big_num_datas.proc_str2_precision_digits) ? 
		   subtract_big_num_datas.proc_str1_precision_digits : subtract_big_num_datas.proc_str2_precision_digits;
        diff_precision_digits = subtract_big_num_datas.result_str_precision_digits - min_precision_digits;
        #ifdef TRACE_DATA
		   printf("TRA: diff - min_prec_digits = %u, max_prec_digits = %u, diff_prec_digits = %u\n", min_precision_digits, subtract_big_num_datas.result_str_precision_digits, diff_precision_digits);
        #endif		
        if(min_precision_digits == subtract_big_num_datas.proc_str1_precision_digits)
		{
			temp_str2_ptr = subtract_big_num_datas.proc_str1_ptr;
			subtract_big_num_datas.proc_str1_ptr = realloc(subtract_big_num_datas.proc_str1_ptr, subtract_big_num_datas.proc_str1_len + 1 + diff_precision_digits);
			if(subtract_big_num_datas.proc_str1_ptr == NULL_DATA_PTR)
			{
				#ifdef TRACE_ERROR
				   printf("ERR: diff - memory allocation failed \n");
				#endif
				if(temp_str2_ptr)
				{
					free(temp_str2_ptr);
				}
				if(subtract_big_num_datas.proc_str2_ptr)
				{
					free(subtract_big_num_datas.proc_str2_ptr);
				}
				return NULL_DATA_PTR;
			}
			#ifdef TRACE_DATA
			   printf("TRA: diff - realloc str1 size : %u, ", subtract_big_num_datas.proc_str1_len);
			#endif
			for(i = 0; i < diff_precision_digits; ++i)
			{
				subtract_big_num_datas.proc_str1_ptr[subtract_big_num_datas.proc_str1_len + i] = 0;
			}
			subtract_big_num_datas.proc_str1_ptr[subtract_big_num_datas.proc_str1_len + i] = NULL_CHAR;
			subtract_big_num_datas.proc_str1_len += diff_precision_digits;			
		}
        else
		{
			temp_str2_ptr = subtract_big_num_datas.proc_str2_ptr;
			subtract_big_num_datas.proc_str2_ptr = realloc(subtract_big_num_datas.proc_str2_ptr, subtract_big_num_datas.proc_str2_len + 1 + diff_precision_digits);
			if(subtract_big_num_datas.proc_str2_ptr == NULL_DATA_PTR)
			{
				#ifdef TRACE_ERROR
				   printf("ERR: diff - memory allocation failed \n");
				#endif
				if(temp_str2_ptr)
				{
					free(temp_str2_ptr);
				}
				if(subtract_big_num_datas.proc_str1_ptr)
				{
					free(subtract_big_num_datas.proc_str1_ptr);
				}
				return NULL_DATA_PTR;
			}
			for(i = 0; i < diff_precision_digits; ++i)
			{
				subtract_big_num_datas.proc_str2_ptr[subtract_big_num_datas.proc_str2_len + i] = 0;
			}
			subtract_big_num_datas.proc_str2_ptr[subtract_big_num_datas.proc_str2_len + i] = NULL_CHAR;
			subtract_big_num_datas.proc_str2_len += diff_precision_digits;
			#ifdef TRACE_DATA
			   printf("TRA: diff - realloc str2 size : %u, ", subtract_big_num_datas.proc_str2_len);
			#endif
		}		
		min_proc_str_len = (subtract_big_num_datas.proc_str1_len < subtract_big_num_datas.proc_str2_len) ? subtract_big_num_datas.proc_str1_len: subtract_big_num_datas.proc_str2_len;
	    max_proc_str_len = (subtract_big_num_datas.proc_str1_len > subtract_big_num_datas.proc_str2_len) ? subtract_big_num_datas.proc_str1_len: subtract_big_num_datas.proc_str2_len;
		//result_alloc_size is included for sign char at begin of result_ptr, '.' char and  NULL_CHAR at end of result_ptr 
		subtract_big_num_datas.result_alloc_size = max_proc_str_len + 3;		
	}
	#ifdef TRACE_DATA
	   printf("result alloc size = %u \n", subtract_big_num_datas.result_alloc_size);
	#endif
	subtract_big_num_datas.result_ptr = calloc(subtract_big_num_datas.result_alloc_size, sizeof(char));
    if(subtract_big_num_datas.result_ptr == NULL_DATA_PTR)
	{
		#ifdef TRACE_ERROR
			   printf("ERR: diff - memory alloc failed \n");
		#endif
		if(subtract_big_num_datas.proc_str1_ptr)
		{
			free(subtract_big_num_datas.proc_str1_ptr);
		}
		if(subtract_big_num_datas.proc_str2_ptr)
		{
			free(subtract_big_num_datas.proc_str2_ptr);
		}
		return NULL_DATA_PTR;
	}		
	diff_proc_str_len = subtract_big_num_datas.proc_str1_len - subtract_big_num_datas.proc_str2_len;
	if(diff_proc_str_len < 0)
	{
		diff_proc_str_len = -diff_proc_str_len;		
	}
	#ifdef TRACE_DATA
	   printf("TRA: diff - min_str_len = %u, max_str_len = %u, max_min_len_diff = %u \n", min_proc_str_len, max_proc_str_len, diff_proc_str_len);
	#endif
	if(subtract_big_num_datas.proc_str1_len < subtract_big_num_datas.proc_str2_len)
	{
		temp_str2_ptr = subtract_big_num_datas.proc_str1_ptr;
		subtract_big_num_datas.proc_str1_ptr = realloc(subtract_big_num_datas.proc_str1_ptr, subtract_big_num_datas.proc_str2_len + 1);
		if(subtract_big_num_datas.proc_str1_ptr == NULL_DATA_PTR)
		{
			#ifdef TRACE_ERROR
			   printf("ERR: diff - memory allocation failed \n");
			#endif
			if(temp_str2_ptr)
			{
				free(temp_str2_ptr);
			}
			if(subtract_big_num_datas.proc_str2_ptr)
			{
				free(subtract_big_num_datas.proc_str1_ptr);
			}
			if(subtract_big_num_datas.result_ptr)
			{
				free(subtract_big_num_datas.result_ptr);
			}
			return NULL_DATA_PTR;
		}
		memmove(subtract_big_num_datas.proc_str1_ptr + diff_proc_str_len, subtract_big_num_datas.proc_str1_ptr, subtract_big_num_datas.proc_str1_len + 1);
		for(i = 0; i < diff_proc_str_len; ++i)
		{
			subtract_big_num_datas.proc_str1_ptr[i] = 0;
		}
		subtract_big_num_datas.proc_str1_len = subtract_big_num_datas.proc_str2_len;
	}
	else if(subtract_big_num_datas.proc_str1_len > subtract_big_num_datas.proc_str2_len)
	{
		temp_str2_ptr = subtract_big_num_datas.proc_str2_ptr;
		subtract_big_num_datas.proc_str2_ptr = realloc(subtract_big_num_datas.proc_str2_ptr, subtract_big_num_datas.proc_str1_len + 1);
		if(subtract_big_num_datas.proc_str2_ptr == NULL_DATA_PTR)
		{
			#ifdef TRACE_ERROR
			   printf("ERR: diff - memory allocation failed \n");
			#endif
			if(temp_str2_ptr)
			{
				free(temp_str2_ptr);
			}
			if(subtract_big_num_datas.proc_str1_ptr)
			{
				free(subtract_big_num_datas.proc_str1_ptr);
			}
			if(subtract_big_num_datas.result_ptr)
			{
				free(subtract_big_num_datas.result_ptr);
			}
			return NULL_DATA_PTR;
		}
		memmove(subtract_big_num_datas.proc_str2_ptr + diff_proc_str_len, subtract_big_num_datas.proc_str2_ptr, subtract_big_num_datas.proc_str2_len + 1);
		for(i = 0; i < diff_proc_str_len; ++i)
		{
			subtract_big_num_datas.proc_str2_ptr[i] = 0;
		}
		subtract_big_num_datas.proc_str2_len = subtract_big_num_datas.proc_str1_len;
	}
	/* 10's complement */
	carry = 1;
    for(i = subtract_big_num_datas.proc_str2_len - 1; i >= 0; --i)
	{
		subtract = (9 - subtract_big_num_datas.proc_str2_ptr[i]) + carry;
		subtract_big_num_datas.proc_str2_ptr[i] = (subtract % 10);
		carry = (subtract / 10);
	}
	zero_subt_str2_carry = carry;
	/* 10's complement subtraction */
	carry = 0;
	for(i = subtract_big_num_datas.proc_str2_len - 1; i >= 0 ; --i)
	{
		subtract = subtract_big_num_datas.proc_str1_ptr[i] + subtract_big_num_datas.proc_str2_ptr[i] + carry;					
		#ifdef TRACE_DATA
			   printf("TRA: diff - str1[%d] = %u, str2[%d] = %u, carry = %d, ", i, subtract_big_num_datas.proc_str1_ptr[i], i, 
			     subtract_big_num_datas.proc_str2_ptr[i], carry);
		#endif
		subtract_big_num_datas.result_ptr[i] = (subtract % 10);
		carry = (subtract / 10);
		#ifdef TRACE_DATA
		   printf("result[%d] = %u \n", i, subtract_big_num_datas.result_ptr[i]);
		#endif
	}
	if(zero_subt_str2_carry == 0 && carry == 0)
	{
		carry = 1;		
		for(i = subtract_big_num_datas.proc_str2_len - 1; i >= 0; --i)
		{
			subtract = (9 - subtract_big_num_datas.result_ptr[i]) + carry;
		    subtract_big_num_datas.result_ptr[i] = (subtract % 10);
		    carry = (subtract / 10);		 
		}
		memmove(subtract_big_num_datas.result_ptr + 1, subtract_big_num_datas.result_ptr, subtract_big_num_datas.proc_str2_len + 1); 
		subtract_big_num_datas.result_ptr[0] = '-';
		result_ptr_init_pos = 1;
	}
	else
	{
		result_ptr_init_pos = 0;
	}
	/* convert result from numeric into ASCII string numeric */
	for (result_ptr_pos = result_ptr_init_pos; result_ptr_pos < max_proc_str_len + result_ptr_init_pos; ++result_ptr_pos)
	{	
		subtract_big_num_datas.result_ptr[result_ptr_pos] += '0';
	}
	#ifdef TRACE_DATA
	   printf("TRA: diff - carry : %u, result: %s before precision \n", carry, subtract_big_num_datas.result_ptr);
	#endif
	if(subtract_big_num_datas.result_str_precision_digits != 0)
	{
		#ifdef TRACE_DATA
	    	printf("TRA: diff - result num precision width: %u \n", subtract_big_num_datas.result_str_precision_digits);
	    #endif		
		memmove(&subtract_big_num_datas.result_ptr[max_proc_str_len + result_ptr_init_pos - subtract_big_num_datas.result_str_precision_digits + 1], 
		  &subtract_big_num_datas.result_ptr[max_proc_str_len + result_ptr_init_pos - subtract_big_num_datas.result_str_precision_digits], subtract_big_num_datas.result_str_precision_digits);
	    subtract_big_num_datas.result_ptr[max_proc_str_len + result_ptr_init_pos - subtract_big_num_datas.result_str_precision_digits] = '.';
		subtract_big_num_datas.result_ptr[subtract_big_num_datas.result_alloc_size - 1] = NULL_CHAR;			
	}
	#ifdef TRACE_DATA
	    printf("TRA: diff - result: %s before removing leading 0 \n", subtract_big_num_datas.result_ptr);
    #endif
	while(subtract_big_num_datas.result_ptr[result_ptr_init_pos] == '0' && subtract_big_num_datas.result_ptr[result_ptr_init_pos + 1] != '.')
	{
	    memmove(&subtract_big_num_datas.result_ptr[result_ptr_init_pos], &subtract_big_num_datas.result_ptr[result_ptr_init_pos + 1], subtract_big_num_datas.result_alloc_size - 1);
	}
    free(subtract_big_num_datas.proc_str1_ptr); 
	free(subtract_big_num_datas.proc_str2_ptr);
	#ifdef TRACE_INFO
	   printf("TRA: In Big num, %s - %s = %s\n", min_str1, subt_str2, subtract_big_num_datas.result_ptr);
	#endif
	return  subtract_big_num_datas.result_ptr;	
} 
