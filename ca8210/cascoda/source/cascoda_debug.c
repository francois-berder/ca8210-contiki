/******************************************************************************/
/*
 * Copyright (c) 2016, Cascoda Limited
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "dev/ca8210/cascoda/include/cascoda_types.h"
#include "dev/ca8210/ports/include/cascoda_bsp.h"
#include "dev/ca8210/cascoda/include/cascoda_debug.h"

#define MAX_PUTC_CHARS  (128)

u8_t PutcCount = 0;
u8_t PutcBuffer[MAX_PUTC_CHARS];
u8_t HexChars[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};


// EVBME_Message Function for Upstream Communications in:
// - cascoda_serial_uart.c
// - cascoda_serial_usb.c
void EVBME_Message( u8_t Count, u8_t *pBuffer );


/******************************************************************************/
/******************************************************************************/
/****** Putc()                                                           ******/
/******************************************************************************/
/****** Brief:  Put Character on Message Buffer                          ******/
/******************************************************************************/
/****** Param:  OutChar - Character to be displayed                      ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void Putc( u8_t OutChar )
{
    if ( OutChar == '\n' )
    {
        dpFlush();
        return;
    }
    PutcBuffer[PutcCount] = OutChar;
    PutcCount++;
    if ( PutcCount == MAX_PUTC_CHARS )
    {
        dpFlush();
    }
} // End of Putc()


/******************************************************************************/
/******************************************************************************/
/****** dpFlush()                                                        ******/
/******************************************************************************/
/****** Brief:  Send Message Upstream                                    ******/
/******************************************************************************/
/****** Param:  -                                                        ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dpFlush( void )
{
    if ( PutcCount != 0 )
    {
        EVBME_Message( PutcCount, PutcBuffer );
        PutcCount = 0;
    }
} // End of dpFlush()


/******************************************************************************/
/******************************************************************************/
/****** dp8()                                                            ******/
/******************************************************************************/
/****** Brief:  DP Hexadecimal 8-bit Unsigned                            ******/
/******************************************************************************/
/****** Param:  Out - Value to be displayed                              ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dp8( u8_t Out )
{
    Putc( HexChars[Out>>4] );
    Putc( HexChars[Out&15] );
} // End of dp8()


/******************************************************************************/
/******************************************************************************/
/****** dp16()                                                           ******/
/******************************************************************************/
/****** Brief:  DP Hexadecimal 16-bit Unsigned                           ******/
/******************************************************************************/
/****** Param:  Out - Value to be displayed                              ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dp16( u16_t Out )
{
    dp8(MS_BYTE(Out));
    dp8(LS_BYTE(Out));
} // End of dp16()


/******************************************************************************/
/******************************************************************************/
/****** dp32()                                                           ******/
/******************************************************************************/
/****** Brief:  DP Hexadecimal 32-bit Unsigned                           ******/
/******************************************************************************/
/****** Param:  Out - Value to be displayed                              ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dp32( u32_t Out )
{
    dp8(LS3_BYTE(Out));
    dp8(LS2_BYTE(Out));
    dp8(LS1_BYTE(Out));
    dp8(LS0_BYTE(Out));
} // End of dp32()


/******************************************************************************/
/******************************************************************************/
/****** dps()                                                            ******/
/******************************************************************************/
/****** Brief:  DP Character String                                      ******/
/******************************************************************************/
/****** Param:  pString - Pointer to String                              ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dps( char *pString )
{
    while ( *pString != 0 )
    {
        Putc(*pString++);
    }
} // End of dps()


/******************************************************************************/
/******************************************************************************/
/****** dptime()                                                         ******/
/******************************************************************************/
/****** Brief:  DP Time HH:MM:SS.MS                                      ******/
/******************************************************************************/
/****** Param:  -                                                        ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dptime( void )
{
//  u16_t MSecs;


//  Putc( (Hours/10)+'0' );
//  Putc( (Hours%10)+'0' );
//  Putc( ':' );
//  Putc( (Minutes/10)+'0' );
//  Putc( (Minutes%10)+'0' );
//  Putc( ':' );
//  Putc( (Seconds/10)+'0' );
//  Putc( (Seconds%10)+'0' );
//  Putc( '.' );
//  MSecs = Ticks;
//  Putc( (MSecs/100)+'0' );
//  Putc( ((MSecs%100)/10)+'0' );
//  dps("  ");
;
} // End of dptime()


/******************************************************************************/
/******************************************************************************/
/****** dparray()                                                        ******/
/******************************************************************************/
/****** Brief:  DP Array of Hexadecimal 8-bit Unsigned                   ******/
/******************************************************************************/
/****** Param:  pArray - Pointer to Array                                ******/
/****** Param:  Length - Length of Array                                 ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dparray( u8_t *pArray, u8_t Length )
{
    while (Length )
    {
        dp8(*pArray++);
        Length--;
    }
} // End of dparray()


/******************************************************************************/
/******************************************************************************/
/****** dparrayle()                                                      ******/
/******************************************************************************/
/****** Brief:  DP Inverse Array of Hexadecimal 8-bit Unsigned           ******/
/******************************************************************************/
/****** Param:  pArray - Pointer to Array                                ******/
/****** Param:  Length - Length of Array                                 ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dparrayle( u8_t *pArray, u8_t Length )
{
    while (Length )
    {
        Length--;
        dp8(pArray[Length]);
    }
} // End of dparrayle()


/******************************************************************************/
/******************************************************************************/
/****** dpc()                                                            ******/
/******************************************************************************/
/****** Brief:  DP Character                                             ******/
/******************************************************************************/
/****** Param:  Out - Value to be displayed                              ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dpc( u8_t Out )
{
    Putc( Out );
} // End of dpc()


/******************************************************************************/
/******************************************************************************/
/****** dpnl()                                                           ******/
/******************************************************************************/
/****** Brief:  DP New Line ('\n')                                       ******/
/******************************************************************************/
/****** Param:  -                                                        ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dpnl( void )
{
    Putc('\n');
} // End of dpnl()


/******************************************************************************/
/******************************************************************************/
/****** dpDec()                                                          ******/
/******************************************************************************/
/****** Brief:  DP 16-Bit Unsigned Decimal                               ******/
/******************************************************************************/
/****** Param:  -                                                        ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dpDec( u16_t Out )
{
    u8_t Sig = 0;
    u16_t Div, Num, Rem;

    Num = Out;
    for ( Div = 10000; Div > 1; Div /= 10 )
    {
        Rem = Num%Div;
        Num = Num/Div;
        if ( Num )
        {
            Sig = 1;
            Putc( HexChars[Num] );
        }
        else if (Sig)
        {
            Putc( '0' );
        }
        Num = Rem;

    }
    Putc( HexChars[Num] );
} // End of dpDec()


/******************************************************************************/
/******************************************************************************/
/****** dp_u8_2h()                                                       ******/
/******************************************************************************/
/****** Brief:  DP u8_t to 2-Digit Hex                                   ******/
/******************************************************************************/
/****** Param:  x - Output Value                                         ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dp_u8_2h(u8_t x)
 {
 Putc( HexChars[x>>4] );
 Putc( HexChars[x&15] );
 } // End of dp_u8_2h()


/******************************************************************************/
/******************************************************************************/
/****** dp_u8_3u()                                                       ******/
/******************************************************************************/
/****** Brief:  DP u8_t to 3-Digit Unsigned                              ******/
/******************************************************************************/
/****** Param:  d - Output Value                                         ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dp_u8_3u(u8_t d)
 {
 u8_t i, num, div, rem, ndone;

 num = d;
 ndone = 0;

 div=100;
 for(i=0;i<2;++i)
  {
  rem = num%div;
  num = num/div;
  if(num)
   {
   ndone = 1;
   Putc(HexChars[num]);
   }
  else
   {
   if(ndone)
    Putc('0');
   else
    Putc(' ');
   }
  num = rem;
  div /= 10;
  }

 Putc(HexChars[num]);

 } // End of dp_u8_3u()


/******************************************************************************/
/******************************************************************************/
/****** dp_u8_u()                                                        ******/
/******************************************************************************/
/****** Brief:  DP u8_t to Variable Length Unsigned                      ******/
/******************************************************************************/
/****** Param:  d - Output Value                                         ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dp_u8_u(u8_t d)
 {
 u8_t i, num, div, rem, ndone;

 num = d;
 ndone = 0;

 div=100;
 for(i=0;i<2;++i)
  {
  rem = num%div;
  num = num/div;
  if(num)
   {
   ndone = 1;
   Putc(HexChars[num]);
   }
  else
   {
   if(ndone)
    Putc('0');
   }
  num = rem;
  div /= 10;
  }

 Putc(HexChars[num]);

 } // End of dp_u8_u()


/******************************************************************************/
/******************************************************************************/
/****** dp_s8_s()                                                        ******/
/******************************************************************************/
/****** Brief:  DP i8_t to Variable Length Signed                        ******/
/******************************************************************************/
/****** Param:  d - Output Value                                         ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dp_s8_s(i8_t d)
 {
 u8_t i, num, div, rem, ndone;

 if(d < 0)
  {
  Putc('-');
  num = -d;
  }
 else
  {
  num = d;
  }
 ndone = 0;

 div=100;
 for(i=0;i<2;++i)
  {
  rem = num%div;
  num = num/div;
  if(num)
   {
   ndone = 1;
   Putc(HexChars[num]);
   }
  else
   {
   if(ndone)
    Putc('0');
   }
  num = rem;
  div /= 10;
  }

 Putc(HexChars[num]);

 } // End of dp_s8_s()


/******************************************************************************/
/******************************************************************************/
/****** dp_u16_5u()                                                      ******/
/******************************************************************************/
/****** Brief:  DP u16_t to 5-Digit Unsigned                             ******/
/******************************************************************************/
/****** Param:  d - Output Value                                         ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dp_u16_5u(u16_t d)
 {
 u8_t i, ndone;
 u16_t num, div, rem;

 num = d;
 ndone = 0;

 div=10000;
 for(i=0;i<4;++i)
  {
  rem = num%div;
  num = num/div;
  if(num)
   {
   ndone = 1;
   Putc(HexChars[num]);
   }
  else
   {
   if(ndone)
    Putc('0');
   else
    Putc(' ');
   }
  num = rem;
  div /= 10;
  }

 Putc(HexChars[num]);

 } // End of dp_u16_5u()


/******************************************************************************/
/******************************************************************************/
/****** dp_u16_u()                                                       ******/
/******************************************************************************/
/****** Brief:  DP u16_t to Variable Length Unsigned                     ******/
/******************************************************************************/
/****** Param:  d - Output Value                                         ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dp_u16_u(u16_t d)
 {
 u8_t i, ndone;
 u16_t num, div, rem;

 num = d;
 ndone = 0;

 div=10000;
 for(i=0;i<4;++i)
  {
  rem = num%div;
  num = num/div;
  if(num)
   {
   ndone = 1;
   Putc(HexChars[num]);
   }
  else
   {
   if(ndone)
    Putc('0');
   }
  num = rem;
  div /= 10;
  }

 Putc(HexChars[num]);

 } // End of dp_u16_u()


/******************************************************************************/
/******************************************************************************/
/****** dp_s16_s()                                                       ******/
/******************************************************************************/
/****** Brief:  DP i16_t to Variable Length Signed                       ******/
/******************************************************************************/
/****** Param:  d - Output Value                                         ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dp_s16_s(i16_t d)
 {
 u8_t i, ndone;
 u16_t num, div, rem;

 if(d < 0)
  {
  Putc('-');
  num = -d;
  }
 else
  {
  num = d;
  }
 ndone = 0;

 div=10000;
 for(i=0;i<4;++i)
  {
  rem = num%div;
  num = num/div;
  if(num)
   {
   ndone = 1;
   Putc(HexChars[num]);
   }
  else
   {
   if(ndone)
    Putc('0');
   }
  num = rem;
  div /= 10;
  }

 Putc(HexChars[num]);

 } // End of dp_s16_s()


/******************************************************************************/
/******************************************************************************/
/****** dp_u32_10u()                                                     ******/
/******************************************************************************/
/****** Brief:  DP u32_t to 10-Digit Unsigned                            ******/
/******************************************************************************/
/****** Param:  d - Output Value                                         ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dp_u32_10u(u32_t d)
 {
 u8_t i, ndone;
 u32_t num, div, rem;

 num = d;
 ndone = 0;

 div=1000000000;
 for(i=0;i<9;++i)
  {
  rem = num%div;
  num = num/div;
  if(num)
   {
   ndone = 1;
   Putc(HexChars[num]);
   }
  else
   {
   if(ndone)
    Putc('0');
   else
    Putc(' ');
   }
  num = rem;
  div /= 10;
  }

 Putc(HexChars[num]);

 } // End of dp_u32_10u()


/******************************************************************************/
/******************************************************************************/
/****** dp_u32_u()                                                       ******/
/******************************************************************************/
/****** Brief:  DP u32_t to Variable Length Unsigned                     ******/
/******************************************************************************/
/****** Param:  d - Output Value                                         ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dp_u32_u(u32_t d)
 {
 u8_t i, ndone;
 u32_t num, div, rem;

 num = d;

 num = d;
 ndone = 0;

 div=1000000000;
 for(i=0;i<9;++i)
  {
  rem = num%div;
  num = num/div;
  if(num)
   {
   ndone = 1;
   Putc(HexChars[num]);
   }
  else
   {
   if(ndone)
    Putc('0');
   }
  num = rem;
  div /= 10;
  }

 Putc(HexChars[num]);

 } // End of dp_u32_u()


/******************************************************************************/
/******************************************************************************/
/****** dpslow()                                                         ******/
/******************************************************************************/
/****** Brief:  DP Character String and wait to clear                    ******/
/******************************************************************************/
/****** Param:  pString - Pointer to String                              ******/
/******************************************************************************/
/****** Return: -                                                        ******/
/******************************************************************************/
/******************************************************************************/
void dpslow( char *pString )
{

dps(pString);
BSP_WaitTicks(50);

} // End of dpslow()