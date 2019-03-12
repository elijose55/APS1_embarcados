/** 
 ** Entrega realizada em parceria com:
 **  - Eli Jose Abi Ghosn
 **  - Maria Eduarda Bicalho
 ** 
 **  - url vídeo
 **/

/********/
/* includes                                                             */
/********/

#include "asf.h"

/********/
/* defines                                                              */
/********/

//*****************************************
#define NOTE_B0  31		//Defining note frequency
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
//*****************************************

//Configuracoes do LED , id 12, PC8

#define LED_PIO           PIOC                  // periferico que controla o LED
#define LED_PIO_ID        12                    // ID do periférico PIOC (controla LED)
#define LED_PIO_IDX       8u                    // ID do LED no PIO
#define LED_PIO_IDX_MASK  (1u << LED_PIO_IDX)   // Mascara para CONTROLARMOS o LED

//Configuracoes do botao SW300 , id 10, PA11



//Configuracoes do (BUZZER) pino PB1 , id 11, PB1

#define BUZZER_PIO			PIOB
#define BUZZER_PIO_ID		11
#define BUZZER_PIO_IDX		1
#define BUZZER_PIO_IDX_MASK (1u << BUZZER_PIO_IDX)

//Configuracoes do (BOTAO2) pino PB0 , id 11, PB0

#define BUT2_PIO			PIOB
#define BUT2_PIO_ID			11
#define BUT2_PIO_IDX		0
#define BUT2_PIO_IDX_MASK (1u << BUT2_PIO_IDX)

//Configuracoes do (BOTAO3) pino PB2 , id 11, PB2

#define BUT3_PIO			PIOB
#define BUT3_PIO_ID			11
#define BUT3_PIO_IDX		2
#define BUT3_PIO_IDX_MASK (1u << BUT3_PIO_IDX)

/********/
/* constants                                                            */
/********/

/********/
/* variaveis globais                                                    */
/********/

/********/
/* prototypes                                                           */
/********/

/********/
/* interrupcoes                                                         */
/********/

/********/
/* funcoes                                                              */
/********/

/**
 * \brief Set a high output level on all the PIOs defined in ul_mask.
 * This has no immediate effects on PIOs that are not outpubut the PIO
 * controller will save the value if they are changed to outputs.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 */
void _pio_set(Pio *p_pio, const uint32_t ul_mask)
{

}


// Função de inicialização do uC
void init(void){
	
	// Initialize the board clock
	sysclk_init();
	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	// Ativa o PIO na qual o LED foi conectado
	pmc_enable_periph_clk(LED_PIO_ID);
	// Inicializa PC8 como saída.
	pio_set_output(LED_PIO, LED_PIO_IDX_MASK, 0, 0, 0);
	
	// Ativa o PIO na qual o BUZZER foi conectado
	pmc_enable_periph_clk(BUZZER_PIO_ID);
	// Inicializa PB1 como saída.
	pio_set_output(BUZZER_PIO, BUZZER_PIO_IDX_MASK, 0, 0, 0);
	

	
	// Inicializa PIO do botao2
	pmc_enable_periph_clk(BUT2_PIO_ID);
	// Inicializa PB0 como entrada com um pull-up.
	pio_set_input(BUT2_PIO,BUT2_PIO_IDX_MASK,PIO_DEFAULT);
	pio_pull_up(BUT2_PIO,BUT2_PIO_IDX_MASK,1);
	
	// Inicializa PIO do botao3
	pmc_enable_periph_clk(BUT3_PIO_ID);
	// Inicializa PB2 como entrada com um pull-up.
	pio_set_input(BUT3_PIO,BUT3_PIO_IDX_MASK,PIO_DEFAULT);
	pio_pull_up(BUT3_PIO,BUT3_PIO_IDX_MASK,1);

}


/********/
/* Main                                                                 */
/********/

// Funcao principal chamada na inicalizacao do uC.
int main(void)
{
	init();
	//*****************************************
	//mario music
	int music3_melody[] = {
	NOTE_E7, NOTE_E7, 0, NOTE_E7,
	0, NOTE_C7, NOTE_E7, 0,
	NOTE_G7, 0, 0,  0,
	NOTE_G6, 0, 0, 0,
	
	NOTE_C7, 0, 0, NOTE_G6,
	0, 0, NOTE_E6, 0,
	0, NOTE_A6, 0, NOTE_B6,
	0, NOTE_AS6, NOTE_A6, 0,
	
	NOTE_G6, NOTE_E7, NOTE_G7,
	NOTE_A7, 0, NOTE_F7, NOTE_G7,
	0, NOTE_E7, 0, NOTE_C7,
	NOTE_D7, NOTE_B6, 0, 0,
	
	NOTE_C7, 0, 0, NOTE_G6,
	0, 0, NOTE_E6, 0,
	0, NOTE_A6, 0, NOTE_B6,
	0, NOTE_AS6, NOTE_A6, 0,
	
	NOTE_G6, NOTE_E7, NOTE_G7,
	NOTE_A7, 0, NOTE_F7, NOTE_G7,
	0, NOTE_E7, 0, NOTE_C7,
	NOTE_D7, NOTE_B6, 0, 0
	};
	int music3_tempo[] = {
		12, 12, 12, 12,
		12, 12, 12, 12,
		12, 12, 12, 12,
		12, 12, 12, 12,
			
		12, 12, 12, 12,
		12, 12, 12, 12,
		12, 12, 12, 12,
		12, 12, 12, 12,
			
		9, 9, 9,
		12, 12, 12, 12,
		12, 12, 12, 12,
		12, 12, 12, 12,
			
		12, 12, 12, 12,
		12, 12, 12, 12,
		12, 12, 12, 12,
		12, 12, 12, 12,
			
		9, 9, 9,
		12, 12, 12, 12,
		12, 12, 12, 12,
		12, 12, 12, 12
		};
	//*****************************************
	//xmas music
	int music1_melody[] = {	
		NOTE_E5, NOTE_E5, NOTE_E5,
		NOTE_E5, NOTE_E5, NOTE_E5,
		NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
		NOTE_E5,
		NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
		NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
		NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
		NOTE_D5, NOTE_G5,
		NOTE_E5, NOTE_E5, NOTE_E5,
		NOTE_E5, NOTE_E5, NOTE_E5,
		NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
		NOTE_E5,
		NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
		NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
		NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
		NOTE_D5, NOTE_G5
	};
	int music1_tempo[] = {
		8, 8, 4,
		8, 8, 4,
		8, 8, 8, 8,
		2,
		8, 8, 8, 8,
		8, 8, 8, 16, 16,
		8, 8, 8, 8,
		4, 4,
		8, 8, 4,
		8, 8, 4,
		8, 8, 8, 8,
		2,
		8, 8, 8, 8,
		8, 8, 8, 16, 16,
		8, 8, 8, 8,
		4, 4
	};
	//*****************************************
	//pirates of the caribbean music
	int music2_melody[] = {
		NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
		NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
		NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
		NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
		NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
		NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
		NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
		NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
		NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
		NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
		NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
		NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
		NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
		NOTE_D5, NOTE_E5, NOTE_A4, 0,
		NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
		NOTE_C5, NOTE_A4, NOTE_B4, 0,

		NOTE_A4, NOTE_A4,
		//Repeat of first part
		NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
		NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
		NOTE_A4, NOTE_G4, NOTE_A4, 0,

		NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
		NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
		NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
		NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
		NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
		NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
		NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
		NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
		NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
		NOTE_D5, NOTE_E5, NOTE_A4, 0,
		NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
		NOTE_C5, NOTE_A4, NOTE_B4, 0,
		//End of Repeat

		NOTE_E5, 0, 0, NOTE_F5, 0, 0,
		NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
		NOTE_D5, 0, 0, NOTE_C5, 0, 0,
		NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

		NOTE_E5, 0, 0, NOTE_F5, 0, 0,
		NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
		NOTE_D5, 0, 0, NOTE_C5, 0, 0,
		NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4			
	};
	int music2_tempo[] = {
  12, 12, 14, 12, 12,
  12, 12, 14, 12, 12,
  12, 12, 14, 12, 12,
  12, 12, 15, 12,
  
  12, 12, 14, 12, 12,
  12, 12, 14, 12, 12,
  12, 12, 14, 12, 12,
  12, 12, 15, 12,
  
  12, 12, 14, 12, 12,
  12, 12, 14, 12, 12,
  12, 12, 14, 12, 12,
  12, 12, 12, 14, 12,

  12, 12, 14, 12, 12,
  14, 12, 14, 12,
  12, 12, 14, 12, 12,
  12, 12, 15, 15,

  14, 12,
  12, 12, 14, 12, 12,
  12, 12, 14, 12, 12,
  12, 12, 15, 12,
  
  12, 12, 14, 12, 12,
  12, 12, 14, 12, 12,
  12, 12, 14, 12, 12,
  12, 12, 15, 12,
  
  12, 12, 14, 12, 12,
  12, 12, 14, 12, 12,
  12, 12, 14, 12, 12,
  12, 12, 12, 14, 12,

  12, 12, 14, 12, 12,
  14, 12, 14, 12,
  12, 12, 14, 12, 12,
  12, 12, 15, 15,
  
  14, 12, 15, 14, 12, 15,
  12, 12, 12, 12, 12, 12, 12, 12, 15,
  14, 12, 15, 14, 12, 15,
  12, 12, 12, 12, 12, 16,

  14, 12, 15, 14, 12, 15,
  12, 12, 12, 12, 12, 12, 12, 12, 15,
  14, 12, 15, 14, 12, 15,
  12, 12, 12, 12, 12, 16
	};
	//*****************************************
	void buzz(long frequency, long length) {
		pio_clear(PIOC, LED_PIO_IDX_MASK); //liga o led de acordo com os toques
		long delayValue = 1000000 / frequency / 2;
		long numCycles = frequency * length / 1000;
		for (long i = 0; i < numCycles; i++) {
			pio_set(BUZZER_PIO, BUZZER_PIO_IDX_MASK);	// Coloca 1 no pino BUZZER
			delay_us(delayValue);						//delay de acordo com a frequencia e duracao do toque
			pio_clear(BUZZER_PIO, BUZZER_PIO_IDX_MASK); // Coloca 0 no pino do BUZZER
			delay_us(delayValue);
		}
		pio_set(PIOC, LED_PIO_IDX_MASK); //liga o led de acordo com os toques
		
	}	
	void play_music(int melody[], int tempo[], int size){
		for (int thisNote = 0; thisNote < size; thisNote++) {
			int noteDuration = 1000 / tempo[thisNote];
			buzz(melody[thisNote], noteDuration);
			if(!(pio_get(BUT3_PIO, PIO_INPUT, BUT3_PIO_IDX_MASK))){ //se o botao de play for pressionado para a musica
				buzz(0, noteDuration);
				delay_s(2);
				return;
			}
			
			int pauseBetweenNotes = noteDuration * 1.10;
			delay_ms(pauseBetweenNotes); //tempo entre os toques
			
			buzz(0, noteDuration);
			}
		}
	int music  = 1;
	// super loop
	// aplicacoes embarcadas não devem sair do while(1).
	while (1)
	{
	if(!(pio_get(BUT3_PIO, PIO_INPUT, BUT3_PIO_IDX_MASK))){ // se o botao de play for clicado toca a musica
		while(!(pio_get(BUT3_PIO, PIO_INPUT, BUT3_PIO_IDX_MASK))){
			delay_ms(10);
		}
		if(music == 1){
			int size = sizeof(music1_melody) / sizeof(int);
			play_music(music1_melody, music1_tempo, size);
				}
		else if(music == 2){
			int size = sizeof(music2_melody) / sizeof(int);
			play_music(music2_melody, music2_tempo, size);
			}
		else if(music == 3){
			int size = sizeof(music3_melody) / sizeof(int);
			play_music(music3_melody, music3_tempo, size);
			}
	}
	
	if(!(pio_get(BUT2_PIO, PIO_INPUT, BUT2_PIO_IDX_MASK)))
	{ // se o botao de trocar for clicado troca de musica
		while(!(pio_get(BUT2_PIO, PIO_INPUT, BUT2_PIO_IDX_MASK)))
		{
			delay_ms(30);
		}		
		if(music == 3){
			music = 1;
			}
		else{
			music++;
			}
	}

	}
	return 0;
	}