/*Um arquivo de registro chamado “clientes.dat” deve armazenar as informações de todos os clientes (Nome ou Razao Social; CPF ou CNPJ). Outro arquivo chamado “produtos.dat” armazena as informações dos produtos (código do produto, descrição e valor unitário).

Faça uma função que permita cadastrar novo cliente (opção 1) e uma função que permita cadastrar um novo produto (opção 2). Inclua também funções para buscar cliente (opção 3) e buscar item (opção 4).

Além disso, o programa deverá ter uma função para emissão de uma nota fiscal (opção 5). Para emissão de uma nota fiscal, o usuário deverá escolher o cliente para o qual se está realizando uma venda, os códigos dos produtos vendidos para este cliente e suas respectivas quantidades. O usuário encerra a inclusão de produtos digitando o valor -1 no código. Não se pode incluir mais que 10 produtos em uma nota fiscal. Após digitar as informações de produtos que deseja, deve-se calcular os totais parciais para cada produto e o total geral (veja o tipo nota descrito abaixo). Essas informações devem ser armazenadas em um arquivo com o seguinte formato de nome “NF-XXXXX.dat” que guarda as informações da nota fiscal emitida pela empresa. Obs: Para cada nota fiscal emitida pela empresa, gera-se um novo arquivo, por isso o nome do arquivo deve ser NF- e o número da nota fiscal que deverá ser de no máximo 5 dígitos (XXXXX).

Por último, faça uma função para ler e imprimir o conteúdo da nota fiscal na tela*/

//Autoria - Luan Vitor Mantelo do Bonfim / RA: 0040961523032 / Jogos Digitais (2º Semestre).


//declaração de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

//perdoa meu typedef com 2 nomes na struct, não deu tempo de arrumar :p


//declaração das structs 
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
//Opção 1
void cadastrocliente (){
	
	//declaração de variáveis
	FILE *file;
	cli cliente;
	char tipo= ' ';
	system ("CLS");

	file=fopen("clientes.dat","ab"); //abre arquivo de clientes para anexo
	
	//se o arquivo não abrir, apresenta msg de erro
	if (file==NULL){
		system ("CLS");
		printf(" Ocorreu um erro ao cadastrar o cliente\n\n");
		system("PAUSE");
	}
	
	else{	//pergunta se é empresa ou pessoa física
			while(strchr("AaBb", tipo)==NULL){
					fflush(stdin);
					printf(" Digite 'A' para pessoa física ou 'B' para razão social: ");
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
				printf(" Falha na gravação\n\n");
				system("PAUSE");
		}
		else{ //caso a gravação não tenha gerado erro, prossegue com o programa
				system ("CLS");
				printf(" Gravação realizada com sucesso\n\n");
				system("PAUSE");
		}
	}//fim do else
fclose(file); //o arquivo "clientes.dat" é fechado
}//fim da função cadastrocliente

//------------------------------------------------------------------------------------
//Opção 2
void cadastroproduto (){
	//declaração de variáveis
	pro produto;
	FILE *file2;
	file2 = fopen("produtos.dat", "ab"); //abre "produtos.dat" para anexo binário
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
			printf("\n Digite o código do produto: ");
			scanf("%d", &produto.codigo);
			fflush(stdin);
			printf("\n Digite o valor unitário do produto: ");
			scanf("%f", &produto.valoruni);
			fflush(stdin);
			
			fwrite (&produto, sizeof (produto), 1, file2); //escreve o que estiver armazenado na struct "produto" em "produtos.dat"

		if(ferror(file2)){
				system ("CLS");
				printf(" Falha na gravação\n\n");
				system("PAUSE");
		}
		else{	//caso a gravação seja bem sucedida, o programa mostra na tela as seguintes frases e prossegue
				system ("CLS");
				printf(" Gravação realizada com sucesso\n\n");
				printf("\n Código do Produto: %d\n\n", produto.codigo);
				printf("\n\n Produto: %s\n", produto.nome);
				printf(" Valor Unitário(R$): %.2f\n\n", produto.valoruni);
				system("PAUSE");
		}
	}//fim do else

fclose(file2); //o arquivo "produtos.dat" é fechado
}//fim da função cadastroproduto

//------------------------------------------------------------------------------------
//opção 3
void buscacliente (){
	//declaração de variáveis
	cli cliente;
	system("CLS");
	FILE *file;
	char num[12];
	int  count=0;
	
	file = fopen("clientes.dat", "rb");//abre o arquivo "clientes.dat" para leitura binária

	printf("\n Digite o numero do CPF/CNPJ do cliente que deseja encontrar: "); //solicita o CPF/CNPJ do cliente para verificação
	gets(num);

	while (!feof(file)){ //enquanto não for o fim do arquivo, continua com as instruções abaixo, caso o cliente seja encontrado, o programa printa, e prossegue

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

	if (count==0){ //se o cliente não for encontrado, o programa mostrará a mensagem abaixo
		system("CLS");
		printf(" \nUsuário não encontrado...\n\n");
		system("PAUSE");
	}

fclose(file);
}//fim da função buscacliente

//------------------------------------------------------------------------------------
//Opção 4
void buscaproduto (){
	//declaração de variáveis
	pro produto;
	system("CLS");
	FILE *file2;
	int count=0, codigo;

	file2 = fopen("produtos.dat", "rb"); //abre o arquivo "produtos.dat" para leitura binária
	
	//caso o arquivo não exista, o programa exibirá na tela a mensagem abaixo
		if(file2==NULL){ 
		system("CLS");
		printf("\n Você ainda não cadastrou produtos no sistema. \n\n");
		exit(1);
	}
	
	//se o arquivo existir, o programa solicita o código para verificação
	fflush(stdin);
	printf("\n Digite o código do produto que deseja encontrar: ");
	scanf("%d", &codigo);


	while (!feof(file2)){ //enquanto não for o fim do arquivo "produtos.dat" 

		if (fread(&produto, sizeof(produto), 1, file2)== 1){ //lendo as structs "produto" 1 a 1 no arquivo, se encontrado o produto, o programa o exibe na tela
			if(codigo==produto.codigo){
				system("CLS");
				printf("\n----------------------\n");
				printf(" Produto encontrado:");
				printf("\n Código do Produto: %d\n\n", produto.codigo);
				printf("\n\n Produto: %s\n", produto.nome);
				printf(" Valor Unitário(R$): %.2f\n\n", produto.valoruni);
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

	if (count==0){ //se o programa não encontrar o produto, exibirá a seguinte mensagem
		system("CLS");
		printf(" \n Produto não encontrado...\n\n");
		system("PAUSE");
	}

fclose(file2);
}//fim da função buscaproduto

//------------------------------------------------------------------------------------
//Opção 5

void geranota (){
	//declaração de variáveis
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
	printf(" Digite o número da nota fiscal: "); //solicita o numero da nota fiscal 
	gets(notaf.numero);

	while(strlen(notaf.numero)>5){ //caso tenha excedido o máximo, exibe na tela
			system("CLS");
			printf("\n Você alcançou o limite de Notas Fiscais (%s / 99999)\n", notaf.numero);
			fflush(stdin);
			printf("\n Digite o número da nota fiscal: ");
			gets(notaf.numero);
	}
	//concatena o nome para que nomeie o arquivo corretamente
	strcat(nome, notaf.numero);
	strcat(nome,".dat");
	strcpy(notaf.nf, nome);

	file3=fopen(nome,"rb"); //abre o arquivo NF-X para leitura binária

	if(file3!=NULL){ //caso o arquivo exista
		fclose(file3); //fecha o arquivo 
		system("CLS");
		char resp=' '; //declaração de resposta como NULL
		printf("\n A nota fiscal %s já existe.", nome);
		while(strchr("sSnN", resp)==NULL){ //enquanto a resposta não for "S" OU "N"
			printf("\n\n Deseja substituí-la (S/N)?: ");
			scanf("%c", &resp);
		}
		if(resp=='s'|| resp=='S'){ //se resposta for "s" o arquivo anterior é removido
			remove(nome);
		}
		if(resp=='n'|| resp=='N'){ //caso seja "n", o programa é fechado
			exit(1);
		}
	}

	fflush(stdin); // limpa teclado
	file = fopen("clientes.dat", "rb"); //abre o arquivo (clientes.dat) para leitura binária
		if(file==NULL){ //caso o arquivo não exista, o programa exibe na tela e é fechado
		system("CLS");
		printf("\n Você ainda não cadastrou clientes no sistema. \n\n");
		exit(1);
		}
	printf("\n Digite CPF/CNPJ do cliente que deseja gerar a NF: "); //caso exista, é solicitado o CPF/CNPJ
	gets(n);

	while (!feof(file)){ // enquanto não for o fim do arquivo 
			if (fread(&cliente, sizeof(cliente), 1, file)== 1){ //leia o tamanho da struct cliente 1 a 1 
				if (strcmp(cliente.cpf, n)==0){ //comparação para ver se o cliente existe no arquivo "clientes.dat"
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
				if (strcmp(cliente.cnpj, n)==0){//comparação para ver se o cliente existe no arquivo "clientes.dat"
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
			if(count==0){ //caso o cliente não exista no arquivo, o programa é fechado
				fflush(stdin);
				printf(" \nUsuário não encontrado...\n\n");
				exit(1);
			} 


// Inclusão de produtos-------------------------------------------------------------------

	fflush(stdin);
	file2=fopen("produtos.dat", "rb"); // abre o arquivo "produtos.dat" para leitura binária

	if(file2==NULL){ //se o arquivo não existir, exibe na tela e fecha o programa
		system("CLS");
		printf("\n Você ainda não cadastrou produtos no sistema. \n\n");
		exit(1);
	}

	fflush(stdin);
	printf("\n Digite o código do produto que deseja incluir: "); //caso o arquivo exista, é solicitado o código
	scanf("%d", &codigo);
		while(i<11){
			while (!feof(file2)){ // enquanto não for fim do arquivo "produtos.dat"
				if (fread(&produto, sizeof(produto), 1, file2)== 1){ // lê structs "produto" de 1 a 1, caso seja encontrado, pronta na tela
						while(codigo==produto.codigo){ //se o código existir no arquivo "produtos.dat"
							system("CLS");
							resposta=' '; //zera resposta para pergunta de inclusão de produtos
							printf("\n----------------------\n");
							printf(" Produto encontrado:");
							printf("\n Código do Produto: %d\n\n", produto.codigo);
							printf("\n\n Produto: %s\n", produto.nome);
							printf(" Valor Unitário(R$): %.2f\n\n", produto.valoruni);
							i++; //incrementa i
							if(i==12){//se o usuário ja tiver incluido 10 produtos, o programa exibe na tela
								system("CLS");
								printf(" Você alcançou o limite de produtos desta NF (10 / 10)\n");
								printf("\n Nota Fiscal gerada com sucesso...\n\n");
								exit(1);
							}
							fflush(stdin);
							printf("\n Digite a quantidade do produto: "); //solicita a quantidade do produto pesquisado
							scanf("%d", &quantidade);
							notaf.total= (produto.valoruni*quantidade); //variável recebe o valor unitário do produto vezes sua quantidade
	
							//cópia de variáveis para a struct notaf
				     		notaf.codigo=codigo; 
							strcpy(notaf.nomep, produto.nome);
							notaf.valoruni=produto.valoruni;
							notaf.quantidade=quantidade;
	
							file3=fopen(nome, "ab"); //abre NF-X para anexo binário
							fwrite(&notaf, sizeof(notaf), 1, file3); //escreve a struct notaf no arquivo 
							fclose(file3);//fecha o arquivo
							rewind(file2);
							while(strchr("sSnN", resposta)==NULL){ // obriga o usuário a responder 's' ou 'n' 
									system("CLS");
									fflush(stdin);
									printf("\n Deseja incluir mais produtos (S/N)? ");
									printf("\n        [%d / 10] ", i);
									scanf("%c", &resposta);
									if(resposta=='S'|| resposta=='s'){//caso a resposta seja "s" o programa solicita novamente o código, reiniciando o ciclo.
											fflush(stdin);
											fclose(file3);
											system("CLS");
											fflush(stdin);
											printf("\n Digite o código do produto que deseja incluir: ");
											scanf("%d", &codigo);
									}
									if(resposta=='n'||resposta=='N'){//caso a resposta seja não o programa fecha os arquivos e mostra na tela 
											system("CLS");
											printf("\n Nota fiscal gerada com sucesso.\n\n");
											fclose(file);
											fclose(file2);
											exit(1);
									}
							}//fim do while(strchr("sSnN", resposta)==NULL)
						} //fim do while (codigo==produto.codigo)
						} //fim do if (fread)
						if (codigo!=produto.codigo){//caso o programa não encontre o produto
								while (fread(&produto, sizeof(produto), 1, file2)==1){
								fflush(stdin);
								system("CLS");
								printf(" \n Produto não encontrado...\n\n");
								system("pause");
								system("CLS");
								printf("\n Digite o código do produto que deseja incluir: ");
								scanf("%d", &codigo);
							}
							}
					} //fim do while (feof)
				} //fim do while (i<11)

fclose(file2);
fclose(file);
system("pause");

}//fim da função geranota

//Opção 6
void printar (){
	//declaração de variáveis
	system("cls");
	nota notaf;
	FILE *file4;
	cli cliente;
	float totalnf;
	char n[20], nome[50]="NF-", tipo[20];
	fflush(stdin);
	 //solicitação de CPF ou CNPJ (para saber a formatação em que será printado o nome do cliente)
	fflush(stdin);
	printf("\n Digite o número do CPF/CNPJ: ");
	gets(tipo);
	//solicitação do número da NF
	fflush(stdin);
	printf("\n Digite o número da nota fiscal: ");
	gets(n);
	//concatenação para gerar o nome do arquivo
	strcat(nome, n);
	strcat(nome, ".dat");
	
	
	
	file4=fopen(nome, "rb"); //abr o arquivo NF-X para leitura binária
	
		while (fread(&notaf, sizeof(notaf),1,file4)==1){//le os blocos totais de bytes da struct (notaf) 1 a 1 no arquivo
			if(strcmp(notaf.cpf, tipo)==0){ //se o cadastro for pessoa física, o programa exibe a informação abaixo
			system("CLS");
			printf(" Nota Fiscal - %s", n);
			printf("\n\n Nome do Cliente: %s\n", notaf.nomec);
			printf(" CPF: %s", notaf.cpf);
			printf("\n--------------------------------------\n\n");
			}
			if(strcmp(notaf.cnpj, tipo)==0){//se o cadastro for empresarial, o programa exibe a informação abaixo
			system("CLS");
			printf(" Nota Fiscal - %s", n);
			printf("\n\n Razão Social do Cliente: %s\n", notaf.nomec);
			printf(" CNPJ: %s", notaf.cnpj);
			printf("\n--------------------------------------\n\n");
			}
		}
	
	fclose(file4);//fecha o arquivo NF-X
	
	file4=fopen(nome, "rb");//abre o arquivo NF-X para leitura binária

	fseek(file4, sizeof(notaf)*1,SEEK_SET); //desloca uma posição tamanho struct (notaf) *referente as informações do cliente
	while (fread(&notaf, sizeof(notaf),1,file4)==1){ //le os blocos totais de bytes da struct (notaf) 1 a 1 no arquivo e exibe sua informação

			printf("\n Código do produto: %d", notaf.codigo);
			printf("\n----------------------\n");
			printf("\n   Nome do produto: %s\n", notaf.nomep);
			printf("\n   Valor unitário: %.2f\n", notaf.valoruni);
			printf("\n   Quantidade: %d\n", notaf.quantidade);
			printf("\n   Valor total do produto: %.2f\n", notaf.total);
			printf("\n\n");
			totalnf=notaf.total+totalnf; //incrementa o valor total de cada produto na variável "totalnf"
	}
	//quando a leitura é finalizada, é exibido o valor total da NF 
	printf("\n TOTAL DA NOTA FISCAL: %.2f", totalnf);


	if(file4==NULL){//caso o arquivo "NF-X" não exista, o programa exibe na tela
		system("cls");
		printf("\n A Nota Fiscal solicitada não existe.\n");
		printf("\n Verifique se o número foi digitado corretamente.\n\n");
	}

printf("\n\n");
system("pause");
fclose(file4);
}//fim da função printar

//------------------------------------------------------------------------------------
// Menu
int main(){
	//declaração de variáveis
	system ("color 03");
	char opcao;
	
	while (opcao != 7){ //enquanto o usuário não quiser sair do programa

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
	printf("\n Escolha uma das opções acima: ");
    opcao=getchar(); //recebe a opção do usuário

   switch(opcao){ //o que fazer em cada opção
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
        printf("\n Sessão Encerrada.\n");
		exit(1);
        break;
        default: printf("\n Opcao invalida.\n\n");
        system("PAUSE");
  }//fim do switch(opcao)
}//	fim do while (opcao != 7)
return 0;
}//Fim do programa

