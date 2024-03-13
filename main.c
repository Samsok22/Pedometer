#include "frdm_bsp.h"
#include "lcd1602.h"
#include "stdio.h"
#include "i2c.h"
#define ZYXDR_Mask 1 << 3 // Maska bitu ZYXDR w rejestrze STATUS

static uint8_t arrayXYZ[6];
static uint8_t sens;
static uint8_t status;

int main(void)
{
    char display[] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20};

    LCD1602_Init(); // Tu jest równiez inicjalizacja portu I2C0
    LCD1602_Backlight(TRUE);

    sens = 0;                                               // Wybór czulosci: 0 - 2g; 1 - 4g; 2 - 8g
    I2C_WriteReg(0x1d, 0x2a, 0x0);                          // ACTIVE=0 - stan czuwania
    I2C_WriteReg(0x1d, 0xe, sens);                          // Ustaw czulosc zgodnie ze zmienna sens
    I2C_WriteReg(0x1d, 0x2a, 0x1);                          // ACTIVE=1 - stan aktywny

    int steps = 0;
		int steps_bieg = 0;
		double wektorzero =1;
    
		
    while(1)
    {
        I2C_ReadReg(0x1d, 0x0, &status);
        status&=ZYXDR_Mask;
        if (status) 
        {
            I2C_ReadRegBlock(0x1d, 0x1, 6, arrayXYZ);

            double x = ((double)((int16_t)((arrayXYZ[0] << 8) | arrayXYZ[1]) >> 2) / (4096 >> sens));
            double y = ((double)((int16_t)((arrayXYZ[2] << 8) | arrayXYZ[3]) >> 2) / (4096 >> sens));
            double z = ((double)((int16_t)((arrayXYZ[4] << 8) | arrayXYZ[5]) >> 2) / (4096 >> sens));

            double accelerationVector = (x * x + y * y + z * z) * (x * x + y * y + z * z) * 1/2; //wektor przyspieszenia

		
					
           
						if (accelerationVector - wektorzero > 0.7)
            {
                steps_bieg++;
                //Wyswietlanie liczby krokow na LCD
                LCD1602_SetCursor(0, 0);
							  sprintf(display, "Trwa pomiar...");
                LCD1602_Print(display);
							  DELAY(300);
            }
						else if (accelerationVector - wektorzero > 0.2)//1.5
            {
                steps++;
                //Wyswietlanie liczby krokow na LCD
                LCD1602_SetCursor(0, 0);
							  sprintf(display, "Trwa pomiar..."); //8 10
                LCD1602_Print(display);
							  DELAY(300);
            }
						else if (steps == 0 && steps_bieg == 0) {
							LCD1602_SetCursor(0, 0);
							sprintf(display,"Brak krokow");
							LCD1602_Print(display);
						}
						else if (steps >= 0 && steps_bieg >=0  && accelerationVector < 1.5) {
							LCD1602_SetCursor(0, 0);
							//sprintf(display,"Wykonales krokow");
							sprintf(display,"Chod:%u Bieg:%u",steps,steps_bieg);
							LCD1602_Print(display);
							LCD1602_SetCursor(0, 1);
							sprintf(display, "Tak trzymaj :)");
							LCD1602_Print(display);
						}
		
        }

       
    }
	}

