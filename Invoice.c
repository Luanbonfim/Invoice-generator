/*Um arquivo de registro chamado �clientes.dat� deve armazenar as informa��es de todos os clientes (Nome ou Razao Social; CPF ou CNPJ). Outro arquivo chamado �produtos.dat� armazena as informa��es dos produtos (c�digo do produto, descri��o e valor unit�rio).

Fa�a uma fun��o que permita cadastrar novo cliente (op��o 1) e uma fun��o que permita cadastrar um novo produto (op��o 2). Inclua tamb�m fun��es para buscar cliente (op��o 3) e buscar item (op��o 4).

Al�m disso, o programa dever� ter uma fun��o para emiss�o de uma nota fiscal (op��o 5). Para emiss�o de uma nota fiscal, o usu�rio dever� escolher o cliente para o qual se est� realizando uma venda, os c�digos dos produtos vendidos para este cliente e suas respectivas quantidades. O usu�rio encerra a inclus�o de produtos digitando o valor -1 no c�digo. N�o se pode incluir mais que 10 produtos em uma nota fiscal. Ap�s digitar as informa��es de produtos que deseja, deve-se calcular os totais parciais para cada produto e o total geral (veja o tipo nota descrito abaixo). Essas informa��es devem ser armazenadas em um arquivo com o seguinte formato de nome �NF-XXXXX.dat� que guarda as informa��es da nota fiscal emitida pela empresa. Obs: Para cada nota fiscal emitida pela empresa, gera-se um novo arquivo, por isso o nome do arquivo deve ser NF- e o n�mero da nota fiscal que dever� ser de no m�ximo 5 d�gitos (XXXXX).

Por �ltimo, fa�a uma fun��o para ler e imprimir o conte�do da nota fiscal na tela*/

//Autoria - Luan Vitor Mantelo do Bonfim / RA: 0040961523032 / Jogos Digitais (2� Semestre).


//declara��o de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

//perdoa meu typedef com 2 nomes na struct, n�o deu tempo de arrumar :p


//declara��o das structs 
typedef struct cliente{
	char cpf[12];
	char cnpj[20];
	char nome[50];
}cli;

typedef struct produto{
	int codigo;
	char nome [50];
	float valoruni;
}pro;

typedef struct notaf{
	char numero[6];
	char nf[50];
	char cpf[12];
	char cnpj[20];
	char nomec[50];
	int codigo;
	int quantidade;
	char nomep[50];
	float valoruni;
	float total;
}nota;



//------------------------------------------------------------------------------------
//Op��o 1
void cadastrocliente (){
	
	//declara��o de vari�veis
	FILE *file;
	cli cliente;
	char tipo= ' ';
	system ("CLS");

	file=fopen("clientes.dat","ab"); //abre arquivo de clientes para anexo
	
	//se o arquivo n�o abrir, apresenta msg de erro
	if (file==NULL){
		system ("CLS");
		printf(" Ocorreu um erro ao cadastrar o cliente\n\n");
		system("PAUSE");
	}
	
	else{	//pergunta se � empresa ou pessoa f�sica
			while(strchr("AaBb", tipo)==NULL){
					fflush(stdin);
					printf(" Digite 'A' para pessoa f�sica ou 'B' para raz�o social: ");
					scanf("%c", &tipo);
			}
			if(tipo=='A'|| tipo=='a'){ 
					fflush(stdin);
					printf("\n Digite o nome do cliente: ");
					gets(cliente.nome);
					fflush(stdin);
					printf(" Digite o cpf do cliente: ");
					gets(cliente.cpf);
			}

			if(tipo=='B'|| tipo=='b'){
					fflush(stdin);
					printf("\n Digite o nome do cliente: ");
					gets(cliente.nome);

					fflush(stdin);
					printf(" Digite o CNPJ do cliente: ");
					gets(cliente.cnpj);
			}
		//escreve os dados da struct (cliente) no arquivo "clientes.dat"
		fwrite (&cliente, sizeof (cliente), 1, file);
		
		if(ferror(file)){
				system ("CLS");
				printf(" Falha na grava��o\n\n");
				system("PAUSE");
		}
		else{ //caso a grava��o n�o tenha gerado erro, prossegue com o programa
				system ("CLS");
				printf(" Grava��o realizada com sucesso\n\n");
				system("PAUSE");
		}
	}//fim do else
fclose(file); //o arquivo "clientes.dat" � fechado
}//fim da fun��o cadastrocliente

//------------------------------------------------------------------------------------
//Op��o 2
void cadastroproduto (){
	//declara��o de vari�veis
	pro produto;
	FILE *file2;
	file2 = fopen("produtos.dat", "ab"); //abre "produtos.dat" para anexo bin�rio
	system ("CLS");
	//caso gere algum erro na abertura do arquivo, apresenta a mensagem abaixo
	if (file2==NULL){
		system ("CLS");
		printf("Ocorreu um erro ao cadastrar o produto");
		system("PAUSE");
	}
	else{ //caso o arquivo seja aberto corretamente o programa prossegue
			fflush(stdin);
			printf("\n Digite o nome do produto: ");
			gets(produto.nome);
			fflush(stdin);
			printf("\n Digite o c�digo do produto: ");
			scanf("%d", &produto.codigo);
			fflush(stdin);
			printf("\n Digite o valor unit�rio do produto: ");
			scanf("%f", &produto.valoruni);
			fflush(stdin);
			
			fwrite (&produto, sizeof (produto), 1, file2); //escreve o que estiver armazenado na struct "produto" em "produtos.dat"

		if(ferror(file2)){
				system ("CLS");
				printf(" Falha na grava��o\n\n");
				system("PAUSE");
		}
		else{	//caso a grava��o seja bem sucedida, o programa mostra na tela as seguintes frases e prossegue
				system ("CLS");
				printf(" Grava��o realizada com sucesso\n\n");
				printf("\n C�digo do Produto: %d\n\n", produto.codigo);
				printf("\n\n Produto: %s\n", produto.nome);
				printf(" Valor Unit�rio(R$): %.2f\n\n", produto.valoruni);
				system("PAUSE");
		}
	}//fim do else

fclose(file2); //o arquivo "produtos.dat" � fechado
}//fim da fun��o cadastroproduto

//------------------------------------------------------------------------------------
//op��o 3
void buscacliente (){
	//declara��o de vari�veis
	cli cliente;
	system("CLS");
	FILE *file;
	char num[12];
	int  count=0;
	
	file = fopen("clientes.dat", "rb");//abre o arquivo "clientes.dat" para leitura bin�ria

	printf("\n Digite o numero do CPF/CNPJ do cliente que deseja encontrar: "); //solicita o CPF/CNPJ do cliente para verifica��o
	gets(num);

	while (!feof(file)){ //enquanto n�o for o fim do arquivo, continua com as instru��es abaixo, caso o cliente seja encontrado, o programa printa, e prossegue

		if (fread(&cliente, sizeof(cliente), 1, file)== 1){ //leitura de structs "cliente" 1 a 1
			if (strcmp(cliente.cpf, num)==0){
				system("CLS");
				printf("\n----------------------\n");
				printf(" Cliente encontrado:");
				printf("\n\n Nome: %s\n", cliente.nome);
				printf(" CPF: %s\n\n", cliente.cpf);
				count++;
				system("PAUSE");
			}
				if (strcmp(cliente.cnpj, num)==0){
				system("CLS");
				printf("\n----------------------\n");
				printf(" Cliente encontrado:");
				printf("\n\n Nome: %s\n", cliente.nome);
				printf(" CNPJ: %s\n\n", cliente.cnpj);
				count++;
				system("PAUSE");
			}
		}
		if (ferror(file)){
			system("CLS");
			printf(" \nERRO NA LEITURA DO ARQUIVO !!\n\n");
			system("PAUSE");
		}

	}// fim do 	while (!feof(file))

	if (count==0){ //se o cliente n�o for encontrado, o programa mostrar� a mensagem abaixo
		system("CLS");
		printf(" \nUsu�rio n�o encontrado...\n\n");
		system("PAUSE");
	}

fclose(file);
}//fim da fun��o buscacliente

//------------------------------------------------------------------------------------
//Op��o 4
void buscaproduto (){
	//declara��o de vari�veis
	pro produto;
	system("CLS");
	FILE *file2;
	int count=0, codigo;

	file2 = fopen("produtos.dat", "rb"); //abre o arquivo "produtos.dat" para leitura bin�ria
	
	//caso o arquivo n�o exista, o programa exibir� na tela a mensagem abaixo
		if(file2==NULL){ 
		system("CLS");
		printf("\n Voc� ainda n�o cadastrou produtos no sistema. \n\n");
		exit(1);
	}
	
	//se o arquivo existir, o programa solicita o c�digo para verifica��o
	fflush(stdin);
	printf("\n Digite o c�digo do produto que deseja encontrar: ");
	scanf("%d", &codigo);


	while (!feof(file2)){ //enquanto n�o for o fim do arquivo "produtos.dat" 

		if (fread(&produto, sizeof(produto), 1, file2)== 1){ //lendo as structs "produto" 1 a 1 no arquivo, se encontrado o produto, o programa o exibe na tela
			if(codigo==produto.codigo){
				system("CLS");
				printf("\n----------------------\n");
				printf(" Produto encontrado:");
				printf("\n C�digo do Produto: %d\n\n", produto.codigo);
				printf("\n\n Produto: %s\n", produto.nome);
				printf(" Valor Unit�rio(R$): %.2f\n\n", produto.valoruni);
				count++;
				system("PAUSE");
			}
		}
		if (ferror(file2)){ //caso haja erro na leitura
			system("CLS");
			printf(" \nERRO NA LEITURA DO ARQUIVO !!\n\n");
			system("PAUSE");
		}
	}

	if (count==0){ //se o programa n�o encontrar o produto, exibir� a seguinte mensagem
		system("CLS");
		printf(" \n Produto n�o encontrado...\n\n");
		system("PAUSE");
	}

fclose(file2);
}//fim da fun��o buscaproduto

//------------------------------------------------------------------------------------
//Op��o 5

void geranota (){
	//declara��o de vari�veis
	cli cliente;
	pro produto;
	nota notaf;
	FILE *file;
	FILE *file2;
	FILE *file3;
	int count=0, codigo, i=1, quantidade;
	char nome[50]="NF-", n[20], resposta=' ';

	system("CLS");
	fflush(stdin);
	printf(" Digite o n�mero da nota fiscal: "); //solicita o numero da nota fiscal 
	gets(notaf.numero);

	while(strlen(notaf.numero)>5){ //caso tenha excedido o m�ximo, exibe na tela
			system("CLS");
			printf("\n Voc� alcan�ou o limite de Notas Fiscais (%s / 99999)\n", notaf.numero);
			fflush(stdin);
			printf("\n Digite o n�mero da nota fiscal: ");
			gets(notaf.numero);
	}
	//concatena o nome para que nomeie o arquivo corretamente
	strcat(nome, notaf.numero);
	strcat(nome,".dat");
	strcpy(notaf.nf, nome);

	file3=fopen(nome,"rb"); //abre o arquivo NF-X para leitura bin�ria

	if(file3!=NULL){ //caso o arquivo exista
		fclose(file3); //fecha o arquivo 
		system("CLS");
		char resp=' '; //declara��o de resposta como NULL
		printf("\n A nota fiscal %s j� existe.", nome);
		while(strchr("sSnN", resp)==NULL){ //enquanto a resposta n�o for "S" OU "N"
			printf("\n\n Deseja substitu�-la (S/N)?: ");
			scanf("%c", &resp);
		}
		if(resp=='s'|| resp=='S'){ //se resposta for "s" o arquivo anterior � removido
			remove(nome);
		}
		if(resp=='n'|| resp=='N'){ //caso seja "n", o programa � fechado
			exit(1);
		}
	}

	fflush(stdin); // limpa teclado
	file = fopen("clientes.dat", "rb"); //abre o arquivo (clientes.dat) para leitura bin�ria
		if(file==NULL){ //caso o arquivo n�o exista, o programa exibe na tela e � fechado
		system("CLS");
		printf("\n Voc� ainda n�o cadastrou clientes no sistema. \n\n");
		exit(1);
		}
	printf("\n Digite CPF/CNPJ do cliente que deseja gerar a NF: "); //caso exista, � solicitado o CPF/CNPJ
	gets(n);

	while (!feof(file)){ // enquanto n�o for o fim do arquivo 
			if (fread(&cliente, sizeof(cliente), 1, file)== 1){ //leia o tamanho da struct cliente 1 a 1 
				if (strcmp(cliente.cpf, n)==0){ //compara��o para ver se o cliente existe no arquivo "clientes.dat"
						count++;
						system("CLS");
						printf("\n----------------------\n");
						printf(" Cliente encontrado:");
						printf("\n\n Nome: %s\n", cliente.nome);
						printf(" CPF: %s\n\n", cliente.cpf);

						strcpy(notaf.nomec, cliente.nome);
						strcpy(notaf.cpf, n);

						file3=fopen(nome,"ab");

						fwrite(&notaf, sizeof(notaf), 1, file3);
						fclose(file3);

				}
				if (strcmp(cliente.cnpj, n)==0){//compara��o para ver se o cliente existe no arquivo "clientes.dat"
						count++;
						system("CLS");

						printf("\n----------------------\n");
						printf(" Cliente encontrado:");
						printf("\n\n Nome: %s\n", cliente.nome);
						printf(" CNPJ: %s\n\n", cliente.cnpj);
						system("pause");

						strcpy(notaf.nomec, cliente.nome);
						strcpy(notaf.cnpj, n);

						file3=fopen(nome,"ab");
						fwrite(&notaf, sizeof(notaf), 1, file3);
						fclose(file3);
				}
			}//fim do if(fread)

			if (ferror(file)){
				system("CLS");
				printf(" \nERRO NA LEITURA DO ARQUIVO !!\n\n");
				system("PAUSE");
			}
	}//fim do while(feof)
			if(count==0){ //caso o cliente n�o exista no arquivo, o programa � fechado
				fflush(stdin);
				printf(" \nUsu�rio n�o encontrado...\n\n");
				exit(1);
			} 


// Inclus�o de produtos-------------------------------------------------------------------

	fflush(stdin);
	file2=fopen("produtos.dat", "rb"); // abre o arquivo "produtos.dat" para leitura bin�ria

	if(file2==NULL){ //se o arquivo n�o existir, exibe na tela e fecha o programa
		system("CLS");
		printf("\n Voc� ainda n�o cadastrou produtos no sistema. \n\n");
		exit(1);
	}

	fflush(stdin);
	printf("\n Digite o c�digo do produto que deseja incluir: "); //caso o arquivo exista, � solicitado o c�digo
	scanf("%d", &codigo);
		while(i<11){
			while (!feof(file2)){ // enquanto n�o for fim do arquivo "produtos.dat"
				if (fread(&produto, sizeof(produto), 1, file2)== 1){ // l� structs "produto" de 1 a 1, caso seja encontrado, pronta na tela
						while(codigo==produto.codigo){ //se o c�digo existir no arquivo "produtos.dat"
							system("CLS");
							resposta=' '; //zera resposta para pergunta de inclus�o de produtos
							printf("\n----------------------\n");
							printf(" Produto encontrado:");
							printf("\n C�digo do Produto: %d\n\n", produto.codigo);
							printf("\n\n Produto: %s\n", produto.nome);
							printf(" Valor Unit�rio(R$): %.2f\n\n", produto.valoruni);
							i++; //incrementa i
							if(i==12){//se o usu�rio ja tiver incluido 10 produtos, o programa exibe na tela
								system("CLS");
								printf(" Voc� alcan�ou o limite de produtos desta NF (10 / 10)\n");
								printf("\n Nota Fiscal gerada com sucesso...\n\n");
								exit(1);
							}
							fflush(stdin);
							printf("\n Digite a quantidade do produto: "); //solicita a quantidade do produto pesquisado
							scanf("%d", &quantidade);
							notaf.total= (produto.valoruni*quantidade); //vari�vel recebe o valor unit�rio do produto vezes sua quantidade
	
							//c�pia de vari�veis para a struct notaf
				     		notaf.codigo=codigo; 
							strcpy(notaf.nomep, produto.nome);
							notaf.valoruni=produto.valoruni;
							notaf.quantidade=quantidade;
	
							file3=fopen(nome, "ab"); //abre NF-X para anexo bin�rio
							fwrite(&notaf, sizeof(notaf), 1, file3); //escreve a struct notaf no arquivo 
							fclose(file3);//fecha o arquivo
							rewind(file2);
							while(strchr("sSnN", resposta)==NULL){ // obriga o usu�rio a responder 's' ou 'n' 
									system("CLS");
									fflush(stdin);
									printf("\n Deseja incluir mais produtos (S/N)? ");
									printf("\n        [%d / 10] ", i);
									scanf("%c", &resposta);
									if(resposta=='S'|| resposta=='s'){//caso a resposta seja "s" o programa solicita novamente o c�digo, reiniciando o ciclo.
											fflush(stdin);
											fclose(file3);
											system("CLS");
											fflush(stdin);
											printf("\n Digite o c�digo do produto que deseja incluir: ");
											scanf("%d", &codigo);
									}
									if(resposta=='n'||resposta=='N'){//caso a resposta seja n�o o programa fecha os arquivos e mostra na tela 
											system("CLS");
											printf("\n Nota fiscal gerada com sucesso.\n\n");
											fclose(file);
											fclose(file2);
											exit(1);
									}
							}//fim do while(strchr("sSnN", resposta)==NULL)
						} //fim do while (codigo==produto.codigo)
						} //fim do if (fread)
						if (codigo!=produto.codigo){//caso o programa n�o encontre o produto
								while (fread(&produto, sizeof(produto), 1, file2)==1){
								fflush(stdin);
								system("CLS");
								printf(" \n Produto n�o encontrado...\n\n");
								system("pause");
								system("CLS");
								printf("\n Digite o c�digo do produto que deseja incluir: ");
								scanf("%d", &codigo);
							}
							}
					} //fim do while (feof)
				} //fim do while (i<11)

fclose(file2);
fclose(file);
system("pause");

}//fim da fun��o geranota

//Op��o 6
void printar (){
	//declara��o de vari�veis
	system("cls");
	nota notaf;
	FILE *file4;
	cli cliente;
	float totalnf;
	char n[20], nome[50]="NF-", tipo[20];
	fflush(stdin);
	 //solicita��o de CPF ou CNPJ (para saber a formata��o em que ser� printado o nome do cliente)
	fflush(stdin);
	printf("\n Digite o n�mero do CPF/CNPJ: ");
	gets(tipo);
	//solicita��o do n�mero da NF
	fflush(stdin);
	printf("\n Digite o n�mero da nota fiscal: ");
	gets(n);
	//concatena��o para gerar o nome do arquivo
	strcat(nome, n);
	strcat(nome, ".dat");
	
	
	
	file4=fopen(nome, "rb"); //abr o arquivo NF-X para leitura bin�ria
	
		while (fread(&notaf, sizeof(notaf),1,file4)==1){//le os blocos totais de bytes da struct (notaf) 1 a 1 no arquivo
			if(strcmp(notaf.cpf, tipo)==0){ //se o cadastro for pessoa f�sica, o programa exibe a informa��o abaixo
			system("CLS");
			printf(" Nota Fiscal - %s", n);
			printf("\n\n Nome do Cliente: %s\n", notaf.nomec);
			printf(" CPF: %s", notaf.cpf);
			printf("\n--------------------------------------\n\n");
			}
			if(strcmp(notaf.cnpj, tipo)==0){//se o cadastro for empresarial, o programa exibe a informa��o abaixo
			system("CLS");
			printf(" Nota Fiscal - %s", n);
			printf("\n\n Raz�o Social do Cliente: %s\n", notaf.nomec);
			printf(" CNPJ: %s", notaf.cnpj);
			printf("\n--------------------------------------\n\n");
			}
		}
	
	fclose(file4);//fecha o arquivo NF-X
	
	file4=fopen(nome, "rb");//abre o arquivo NF-X para leitura bin�ria

	fseek(file4, sizeof(notaf)*1,SEEK_SET); //desloca uma posi��o tamanho struct (notaf) *referente as informa��es do cliente
	while (fread(&notaf, sizeof(notaf),1,file4)==1){ //le os blocos totais de bytes da struct (notaf) 1 a 1 no arquivo e exibe sua informa��o

			printf("\n C�digo do produto: %d", notaf.codigo);
			printf("\n----------------------\n");
			printf("\n   Nome do produto: %s\n", notaf.nomep);
			printf("\n   Valor unit�rio: %.2f\n", notaf.valoruni);
			printf("\n   Quantidade: %d\n", notaf.quantidade);
			printf("\n   Valor total do produto: %.2f\n", notaf.total);
			printf("\n\n");
			totalnf=notaf.total+totalnf; //incrementa o valor total de cada produto na vari�vel "totalnf"
	}
	//quando a leitura � finalizada, � exibido o valor total da NF 
	printf("\n TOTAL DA NOTA FISCAL: %.2f", totalnf);


	if(file4==NULL){//caso o arquivo "NF-X" n�o exista, o programa exibe na tela
		system("cls");
		printf("\n A Nota Fiscal solicitada n�o existe.\n");
		printf("\n Verifique se o n�mero foi digitado corretamente.\n\n");
	}

printf("\n\n");
system("pause");
fclose(file4);
}//fim da fun��o printar

//------------------------------------------------------------------------------------
// Menu
int main(){
	//declara��o de vari�veis
	system ("color 03");
	char opcao;
	
	while (opcao != 7){ //enquanto o usu�rio n�o quiser sair do programa

	fflush(stdin);
	system("CLS");
	//exibe o menu
	printf("++++++++++++++++++++++++++++++++++++++++++\n");
    printf("          CADASTRO DE PRODUTOS\n");
    printf("++++++++++++++++++++++++++++++++++++++++++\n\n");
    printf(" 1.Cadastrar Novo Cliente\n\n");
    printf(" 2.Cadastrar Novo Item\n\n");
    printf(" 3.Buscar Cliente\n\n");
    printf(" 4.Buscar Item\n\n");
    printf(" 5.Gerar Nota Fiscal\n\n");
	printf(" 6.Imprimir Nota Fiscal\n\n");
	printf(" 7.Sair\n\n");
	printf("\n ----------------------------- ");
	printf("\n Escolha uma das op��es acima: ");
    opcao=getchar(); //recebe a op��o do usu�rio

   switch(opcao){ //o que fazer em cada op��o
		case '1': cadastrocliente();
        break;
        case '2': cadastroproduto();
        break;
        case '3': fflush(stdin);
				  buscacliente();
        break;
        case '4': fflush(stdin);
				  buscaproduto();
        break;
        case '5': fflush(stdin);
		          geranota();
        break;
        case '6': fflush(stdin);
		          printar();
        break;
        case '7': system("CLS");
        printf("\n Sess�o Encerrada.\n");
		exit(1);
        break;
        default: printf("\n Opcao invalida.\n\n");
        system("PAUSE");
  }//fim do switch(opcao)
}//	fim do while (opcao != 7)
return 0;
}//Fim do programa

