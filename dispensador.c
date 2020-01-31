#include <16f877a.h>
#fuses HS, NOWDT // High Speed oscilator and Not Watch Dog Timer
#use delay (clock=4M)

#include <lcd.c>

char msg1[] = {"HA INTRODUCIDO"};
char msg2[] = {"DEVOLUCION"};

char pro1[16]={"COCA-COLA"}; 
char pro2[16]={"RIZADAS"}; 
char pro3[16]={"YUPIS"}; 
char pro4[16]={"CHOCOLATINAS"}; 

float dinero=0, vueltos=0;

short validarDinero(char mostrar);
void pagarProducto(char producto, float precio);
void mostrarMensaje(char *fila1, float fila2);

void main (){
   int car;
   set_tris_d(0); // en caso de poner solo pines de salida
   lcd_init();    // Inicializa el LCD
   while (true){
      if (validarDinero(0)==0) {
         lcd_gotoxy (1, 1);                    // Situa cursor en columna 1, fila 1
         printf(lcd_putc, "VENTA ALIMENTOS "); 
         lcd_gotoxy (1, 2);                    // Situa cursor en columna 1, fila 2
         printf(lcd_putc, "   BIENVENIDO   ");
      } else {
         mostrarMensaje(msg1, dinero);
      }
 
      // En caso de presionar los toggles de dinero en la entradas del PUERTO B
      if (input(PIN_B0)==1) {
         dinero += 100;
      }
      if (input(PIN_B1)==1) {
         dinero += 200;
      }
      if (input(PIN_B2)==1) {
         dinero += 500;
      }
      if (input(PIN_B3)==1) {
         dinero += 1000;
      }
      
      /*
       * Dependiendo del producto seleccionado se mostrará información
       * en el LCD y se hará el cobro respectivo
       */
      if (input(PIN_A1)==1) {
          if (validarDinero(1)==1) {
             mostrarMensaje(pro1, 1700);
             pagarProducto(0, 1700);
          }
      }
      if (input(PIN_A2)==1) {
          if (validarDinero(1)==1) {
             mostrarMensaje(pro2, 1500);
             pagarProducto(1, 1500);
          }
      }
      if (input(PIN_A3)==1) {
          if (validarDinero(1)==1) {
             mostrarMensaje(pro3, 1300);
             pagarProducto(2, 1300);
          }
      }
      if (input(PIN_A4)==1) {
          if (validarDinero(1)==1) {
             mostrarMensaje(pro4, 500);
             pagarProducto(3, 500);
          }
      }
      
      delay_ms(1000); // Retardo de 1 segundo
      lcd_putc("\f"); // Limpia pantalla
   }
}

/**
 * Función encargada de imprimir en el display LCD
 *
 * @param char *fila1 Puntero de cadena para la primera fila del LCD
 * @param float fila2 Texto de dinero en la segunda fila del LCD 
 */
void mostrarMensaje(char *fila1, float fila2) {
    lcd_putc("\f");                       // Limpia pantalla
    lcd_gotoxy (1, 1);                    // Situa cursor en columna 1, fila 1
    printf(lcd_putc, fila1); 
    lcd_gotoxy (1, 2);                    // Situa cursor en columna 1, fila 1
    printf(lcd_putc, "COP $ %f", fila2); 
}

/**
 * Función encargada de hacer el cobro respectivo por producto
 *
 * @param char producto Producto a cobrar
 * @param float precio  Precio del producto a cobrar
 */
void pagarProducto(char producto, float precio) {
    vueltos = dinero - precio;
    
    // Se valida que haya ingresado más dinero que el valor del producto
    if (vueltos<0) {
       lcd_putc("\f");                       // Limpia pantalla
       lcd_gotoxy (1, 1);                    // Situa cursor en columna 1, fila 1
       printf(lcd_putc, "NO LE ALCANZA"); 
       lcd_gotoxy (1, 2);                    // Situa cursor en columna 1, fila 1
       printf(lcd_putc, "PARA EL PRODUCTO"); 
    } else {
       dinero = 0; // Se deja la variable dinero a 0
       lcd_putc("\f");                       // Limpia pantalla
       lcd_gotoxy (1, 1);                    // Situa cursor en columna 1, fila 1
       printf(lcd_putc, "HA COMPRADO"); 
         switch(producto) {
           case 0:
               lcd_gotoxy (1, 2);                    // Situa cursor en columna 1, fila 2
               printf(lcd_putc, pro1); 
               break;
           case 1:
               lcd_gotoxy (1, 2);                    // Situa cursor en columna 1, fila 2
               printf(lcd_putc, pro2); 
               break;
           case 2:
               lcd_gotoxy (1, 2);                    // Situa cursor en columna 1, fila 2
               printf(lcd_putc, pro3); 
               break;
           case 3:
               lcd_gotoxy (1, 2);                    // Situa cursor en columna 1, fila 2
               printf(lcd_putc, pro4); 
               break;
       }
       
       delay_ms(3000);                       // Retardo de 3 segundos
       mostrarMensaje(msg2, vueltos);
       delay_ms(3000);                       // Retardo de 3 segundos
    }
}

/**
 * Función encargada de validar si se ha introducido dinero
 *
 * @param char mostrar "Booleano", en caso de estar activado se muestra mensaje
 *                     de que aún no ha ingresado dinero
 *
 * @return boolean
 */
short validarDinero(char mostrar) {
   if (dinero==0) {
       if (mostrar==1) {
          lcd_putc("\f");                       // Limpia pantalla
          lcd_gotoxy (1, 1);                    // Situa cursor en columna 1, fila 1
          printf(lcd_putc, "AUN NO INGRESA"); 
          lcd_gotoxy (1, 2);                    // Situa cursor en columna 1, fila 2
          printf(lcd_putc, "DINERO"); 
       }
       return 0;
   } else {
       return 1;
   }   
}
