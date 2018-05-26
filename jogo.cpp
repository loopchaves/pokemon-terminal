#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace std;

typedef int TipoChave;

#define NUM_MOVES 4

typedef struct TipoMove{
	string nome; 
	int id;
	char tipo; //'e' para especial e 'f' para fisico 
	float power;
} TipoMove; 
	
typedef struct TipoPokemon{
	TipoChave id;
	string nome;
	float atk; //ataque
	float def; //defesa
	float hp; //vida
	float speed; //velocidade (o maior ataca antes)
	float sp_atk; //ataque especial
	float sp_def; //defesa especial
	TipoMove moves[NUM_MOVES]; //movimentos de ataque possiveis
} TipoPokemon;

typedef struct TipoNo *TipoApontador;

typedef struct TipoNo {
	TipoPokemon pokemon;
	struct TipoNo *prox;
} TipoNo;

typedef struct TipoLista {
	TipoApontador Primeiro, Ultimo;
} TipoLista;

////////////////////////////////////////////////////////////////////////

void InicializaMove(TipoMove *mov, string n, int id, char t, float pw){
	mov->nome = n;
	mov->id = id;
	mov->tipo = t;
	mov->power = pw;
	
	//cout << "move " << mov->nome << " inicializado " << endl;
}

void InicializaLista(TipoLista *L) {
	(*L).Primeiro = NULL;
	(*L).Ultimo = NULL;
	printf("Criou a lista\n");
}

int ListaVazia(TipoLista *L) {
	if (L->Primeiro == NULL)
		return 1;
	else
		return 0;
}

void InsereLista(TipoLista *L, TipoPokemon poke) {

	TipoApontador P;
	
	P = (TipoApontador) malloc(sizeof(TipoNo));
	if (P == NULL) {
		cout << "NAO FOI POSSIVEL INSERIR O ITEM: MEMORIA CHEIA " << endl;
		return;
	}
	
	P->pokemon = poke;
	P->prox = NULL;
	if (ListaVazia(L)) {
		L->Primeiro = P;
		L->Ultimo = P;
	} else {
		L->Ultimo->prox = P;
		L->Ultimo = P;
	}

	cout << "Pokemon inserido: " << poke.id << endl;
}

TipoApontador PesquisaLista(TipoLista *L, TipoChave C) {

	TipoApontador P;
	
	P = L->Primeiro;
	while(P != NULL) {
		//printf("Pesquisa passando por %d\n", P->poke.Chave);
		if (P->pokemon.id == C)
			return P;
		P = P->prox;
	}
	//caso nao encontre
	cout << "nao encontrado" << endl;
	
	return NULL; 
}

TipoPokemon PrimeiroPokemon(TipoLista *L){
	TipoPokemon ash;
	ash.id = -1;
	
	if(ListaVazia(L)){
		cout << "a lista esta vazia, nao eh possivel retornar o primeiro " << endl;
		return ash;
	}
	
	return L->Primeiro->pokemon; 
}

void InicializaPokemon(TipoPokemon *poke, int id, string nome, float ataque, float defesa, float vida, float velocidade, float spAtk, float spDef, TipoMove mov0, TipoMove mov1, TipoMove mov2, TipoMove mov3){			
								
				poke->id = id;
				poke->nome = nome;
				poke->atk = ataque;
				poke->def = defesa;
				poke->hp = vida;
				poke->speed = velocidade;
				poke->sp_atk = spAtk;
				poke->sp_def = spDef;
				poke->moves[0]= mov0;
				poke->moves[1] = mov1;
				poke->moves[2] = mov2;
				poke->moves[3] = mov3;		
																			
}

void ImprimePokemon(TipoPokemon *poke){
	
	cout << endl;
	cout << "****************************" << endl;
	cout << "*  NOME:	" <<  poke->nome  << "	           *" << endl;
//	cout << "*  ID: " << poke->id << "                   *" << endl;
//	cout << "*  ATK: " << poke->atk << "	           *" << endl;	
//	cout << "*  DEF: " << poke->def << "	           *" << endl;
	cout << "*  HP: " << poke->hp << "	           *" << endl;
	cout << "*  SPEED: " << poke->speed << "	           *" << endl;
//	cout << "*  SP.ATK: " << poke->sp_atk << "	           *" << endl;
//	cout << "*  SP.DEF:	" << poke->sp_def << " 	   *" << endl;
//	cout << "*  MOVES: " << "                 *" << endl;
//	cout << "*  "<< poke->moves->nome << "            *" << endl;
//	cout << "*  "<< poke->moves[1].nome << "              *" << endl;
//	cout << "*  "<< poke->moves[2].nome << "                     *" << endl;
//	cout << "*  "<< poke->moves[3].nome << "              *" << endl;
	cout << "****************************" << endl; 
} 

void Ataque(TipoPokemon *ataca, TipoPokemon *defende, TipoMove *move){

	cout << endl;
	float dano;
	
	cout <<"Tipo do move usado: " << move->tipo << endl;

	if(move->tipo == 'e'){ //ataque especial atinge defesa especial
		cout << "ataque especial" << endl;
		dano = ((ataca->sp_atk / defende->sp_def) * move->power)/2;
	}
	else if(move->tipo == 'f'){ //ataque fisico atinge defesa normal
		cout << "ataque fisico" << endl;

		dano = ((ataca->atk / defende->def) * move->power)/2;	
	}
	else{
		//tipo invalido
		cout << "tipo invalido" << endl;
	}

	//trunca o dano para ficar inteiro
	dano = floor(dano);
	
	cout << "dano: " << dano << endl;

	//decrementa a hp do pokemon que recebeu o ataque
	defende->hp = defende->hp - dano; 

	cout << ataca->nome << " atacou " << defende->nome << " usando " << move->nome << " e causou " << dano << " de dano";
}

//metodo para escolha do move a ser jogado
void ImprimeMoves(TipoPokemon *pokemon, TipoMove *escolhido){	
	
	int n_escolhido = 0;
	cout << "Escolha o move: " << endl;
	for(int i = 0; i < NUM_MOVES; i++){
		cout << "(" << i+1 << ") " << pokemon->moves[i].nome << endl;
	}
	cin >> n_escolhido;

	*escolhido = pokemon->moves[n_escolhido-1];
}

TipoPokemon comeca(TipoPokemon pokemon1, TipoPokemon pokemon2){
	//determina qual joga primeiro
	if(pokemon1.speed > pokemon2.speed){
		//pokemon1 comeca
		cout << endl;
		cout << "speed do " << pokemon1.nome <<" maior, ele comeca" << endl;
		return pokemon1;
		
	} else
	{
		//pokemon2 comeca
		cout << endl;
		cout << "speed do " << pokemon2.nome <<" maior, ele comeca" << endl;
		return pokemon2;
	}
}

int main(int argc, char** argv)
{

	cout << "Inicializando moves :) " << endl << endl; 
	TipoMove flamethrower; 
	TipoMove fire_blast; 
	TipoMove fly; 
	TipoMove earthquake;
	
	TipoMove quick_attack;
	TipoMove thunderbolt;
	TipoMove thunder;
	TipoMove skull_bash;
	
	InicializaMove(&flamethrower, "Flamethrower", 1, 'e', 95); 
	InicializaMove(&fire_blast, "Fire Blast", 2, 'e', 120);
	InicializaMove(&fly, "Fly", 3, 'f', 70);
	InicializaMove(&earthquake, "Earthquake", 4, 'f', 100);
	
	InicializaMove(&quick_attack, "Quick Attack", 5, 'f', 40);
	InicializaMove(&thunderbolt, "Thunderbolt", 6, 'e', 95);
	InicializaMove(&thunder, "Thunder", 7, 'e', 120);
	InicializaMove(&skull_bash, "Skull Bash", 8, 'f', 100);
	
	cout << "Inicializando pokemons :) " << endl << endl; 	
	
TipoPokemon charizard;
	TipoPokemon pikachu;
		
	InicializaPokemon(&charizard, 2, "Charizard", 293, 280, 360, 328, 348, 295, flamethrower, fire_blast, fly, earthquake);
	
	ImprimePokemon(&charizard);
	
	TipoLista player1, player2;
	InicializaLista(&player1);
	InicializaLista(&player2);
	
	InsereLista(&player1, charizard);
	
	InicializaPokemon(&pikachu, 1, "Pikachu", 229, 196, 274, 306, 218, 218, quick_attack, thunderbolt, thunder, skull_bash);
	
	ImprimePokemon(&pikachu);

	InsereLista(&player2, pikachu);

	//no começo do jogo, pega os primeiros da lista de cada jogador	
	
	TipoPokemon pokemon1 = PrimeiroPokemon(&player1);
	TipoPokemon pokemon2 = PrimeiroPokemon(&player2);
	
	TipoPokemon primeiro = comeca(pokemon1, pokemon2);

	/*

	//determina qual joga primeiro
	if(pokemon1.speed > pokemon2.speed){
		//pokemon1 comeca
		cout << endl;
		cout << "speed do pokemon 1 maior, ele comeca" << endl;
		
	} else
	{
		//pokemon2 comeca
		cout << endl;
		cout << "speed do pokemon 2 maior, ele comeca" << endl;
	}

	*/
	
	TipoMove escolhido;	

	ImprimeMoves(&primeiro, &escolhido);
	
	Ataque(&charizard, &pikachu, &escolhido);	
	
	ImprimePokemon(&pikachu);
	
	return 0;
}
