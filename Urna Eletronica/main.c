#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char nome[40];
    char num[4];
    int partido;
    char sigla[4];
    int numvoto; //ADICIONEI A VARIAVEL PARA JUNTAR O PARTIDO NO NUMERO DO CANDIDATO, FEITA NO ARQUIVO TEXTO
    int votos; // TODOS OS VEREADORES COMEÇAM COM 0 VOTOS
} vereador;

typedef struct {
    char nome[40];
    int num; // ELEITORES VOTAM DIRETAMENTE NO NUMERO DO CANDIDATO
    char sigla[4];
    int votos; // VOTOS INICIAM A ZERO
} prefeito;

typedef struct {
    char nome[40];
    int titulo; // TITULO USADO PARA VOTAR 
    char deficiencia[2];
    char presenca[2]; // MARCADOR SE O ELEITOR FOI VOTAR
    int contador; // CONTADOR PARA IDENTIFICAR SE O ELEITOR VOTOU, SE 0, NAO VOTOU, SE 1, VOTOU
} eleitor;

typedef struct{
    char sigla[4];
    int partido; // PARTIDOS CADASTRADOS 
    int votos; // QUANTIDADE DE VOTOS DE CADA PARTIDO
}partidos;

vereador listaVereador[100]; // PODEM TER ATÉ 100 VEREADORES NA LISTA
prefeito listaPrefeito[10]; // PODEM TER ATÉ 10 PREFEITOS NA LISTA
eleitor listaEleitor[MAX]; // PODEM TER ATÉ 300 ELEITORES NA LISTA
partidos listaPartidos[5]; // PODEM TER ATÉ 5 PARTIDOS NA LISTA

void registroVereadores(vereador listaVereador[]) {
    int i = 0;
    char linha[100];
    FILE *ponteiroVereador;
    
    ponteiroVereador = fopen("vereadores.txt", "r"); // ABRE O ARQUIVO JA EXISTENTE DE VEREADORES
    if (ponteiroVereador == NULL) // SE NAO EXISTIR ARQUIVO, O PROGRAMA SE ENCERRA
        exit(1);

    while (fgets(linha, sizeof(linha), ponteiroVereador) != NULL) { // LE O ARQUIVO E JOGA NAS VARIAVEIS CORRESPONDENTES
        sscanf(linha, "%39[^;];%3s;%d;%3s;%d", listaVereador[i].nome, listaVereador[i].num, &listaVereador[i].partido, listaVereador[i].sigla, &listaVereador[i].numvoto);
        i++;
    }

    fclose(ponteiroVereador);
}

void registroPrefeitos(prefeito listaPrefeito[]) {
    int i = 0;
    char linha[100];
    FILE *ponteiroPrefeito;

    ponteiroPrefeito = fopen("prefeitos.txt", "r"); // ABRE O ARQUIVO JA EXISTENTE DE PREFEITOS
    if (ponteiroPrefeito == NULL)// SE NAO EXISTIR ARQUIVO, O PROGRAMA SE ENCERRA
        exit(1);

    while (fgets(linha, sizeof(linha), ponteiroPrefeito) != NULL) { // LE O ARQUIVO E JOGA NAS VARIAVEIS CORRESPONDENTES
        sscanf(linha, "%39[^;];%d;%3s", listaPrefeito[i].nome, &listaPrefeito[i].num, listaPrefeito[i].sigla);
        i++;
    }

    fclose(ponteiroPrefeito);
}

void registroEleitores(eleitor listaEleitor[]) {
    int i = 0;
    char linha[100];
    FILE *ponteiroEleitor;

    ponteiroEleitor = fopen("eleitores.txt", "r"); // ABRE O ARQUIVO JA EXISTENTE DE ELEITORES
    if (ponteiroEleitor == NULL)// SE NAO EXISTIR ARQUIVO, O PROGRAMA SE ENCERRA
        exit(1);

    while (fgets(linha, sizeof(linha), ponteiroEleitor) != NULL ) { // LE O ARQUIVO E JOGA NAS VARIAVEIS CORRESPONDENTES
        sscanf(linha, "%39[^;];%d;%1s;%1s", listaEleitor[i].nome, &listaEleitor[i].titulo, listaEleitor[i].deficiencia, listaEleitor[i].presenca);
        i++;
    }

    fclose(ponteiroEleitor);
}

void registroPartidos(partidos listaPartidos[]){
    listaPartidos[0].partido = 10; // PARTIDO 10 -- ABC
    listaPartidos[1].partido = 20; // PARTIDO 20 -- XYZ
    listaPartidos[2].partido = 30; // PARTIDO 30 -- BSB
    listaPartidos[3].partido = 40; // PARTIDO 40 -- AAA
    listaPartidos[4].partido = 50; // PARTIDO 50 -- SOL

    strcpy(listaPartidos[0].sigla, "ABC"); // PARTIDO 10 -- ABC
    strcpy(listaPartidos[1].sigla, "XYZ"); // PARTIDO 20 -- XYZ
    strcpy(listaPartidos[2].sigla, "BSB"); // PARTIDO 30 -- BSB
    strcpy(listaPartidos[3].sigla, "AAA"); // PARTIDO 40 -- AAA
    strcpy(listaPartidos[4].sigla, "SOL"); // PARTIDO 50 -- SOL
}

void votacao(eleitor listaEleitor[], int votosVereador[], int votosPrefeito[], int *presentes) {
    int j = 0;
    int auxiliar; // VARIAVEL PARA O EMBARALHAMENTO DOS VOTOS
    int titulo; // VARIAVEL PARA AUTENTICAÇÃO DO ELEITOR
    int tituloCorreto = 0; // VARIAVEL PARA PERMIÇÃO DO ELEITOR A VOTAR

    for (int i = 0; i < MAX; i++) {
        if (strcmp(listaEleitor[i].presenca, "S") == 0) { // SE O ELEITOR COMPARECER A ELEIÇÃO, ELE PODE VOTAR
            system("cls");
            tituloCorreto = 0;
            while (tituloCorreto == 0) { // SE O ELEITOR DIGITAR O TITULO CORRETO, ELE PODE VOTAR
                printf("Digite o seu titulo de eleitor: \n");
                scanf("%d", &titulo);
                for(int k = 0 ; k < MAX ; k++){
                if (titulo == listaEleitor[k].titulo && (strcmp(listaEleitor[k].presenca, "S") == 0) && listaEleitor[k].contador == 0){// SE O ELEITOR DIGITAR O TITULO CORRETO, SE O ELEITOR ESTAVA PRESENTE E SE ELE NAO VOTOU AINDA, ELE PODE VOTAR
                    tituloCorreto = 1; // ELEITOR DIGITOU O TITULO CORRETO
                    printf("%s, Digite o seu voto para vereador: \n", listaEleitor[i].nome);
                    printf("Voto no candidato: 5 digitos \n");
                    printf("Voto no partido: 2 digitos \n");
                    printf("Votar em branco: 0 \n");
                    printf("Votar nulo: 1 \n");
                    printf("Votos em candidatos inexistentes serao anulados \n");
                    scanf("%d", &votosVereador[j]); // JOGA O VOTO EM VEREADORES NA VARIAVEL
                    getchar();

                    printf("%s, Digite o seu voto para prefeito em dois digitos: \n", listaEleitor[i].nome);
                    printf("Votar em branco: 0 \n");
                    printf("Votar nulo: 1 \n");
                    printf("Votos em candidatos inexistentes serao anulados \n");
                    scanf("%d", &votosPrefeito[j]); // JOGA O VOTO EM PREFEITOS NA VARIAVEL
                    getchar();
                    listaEleitor[k].contador = 1; // ELEITOR VOTOU
                }}}
            system("cls"); // LIMPA A TELA

            if (j % 2 == 0 || j == 1) { // EMBARALHAR OS VOTOS PARA SEGURANÇA
                auxiliar = votosVereador[0];
                votosVereador[0] = votosVereador[j];
                votosVereador[j] = auxiliar;

                auxiliar = votosPrefeito[0];
                votosPrefeito[0] = votosPrefeito[j];
                votosPrefeito[j] = auxiliar;
            }
            j++;
            (*presentes)++; // VARIAVEL DE PESSOAS PRESENTES NA VOTAÇÃO
}}}

void gravarVotosBinariosVereadores(int presentes, int votosVereador[]) {
    FILE *ponteiroArqBinarioV;
    ponteiroArqBinarioV = fopen("binario_vereador.dat", "wb"); // CRIA UM ARQUIVO BINARIO PARA GUARDAR OS VOTOS EM VEREADOR

    if (ponteiroArqBinarioV == NULL)
        exit(1);

    fwrite(votosVereador, sizeof(int), presentes, ponteiroArqBinarioV); // TRANSFERE OS DADOS DO VETOR PARA O ARQUIVO BINARIO  

    fclose(ponteiroArqBinarioV);

    memset(votosVereador, 0, sizeof(int) * MAX); // ZERA O VETOR DE VOTOS EM VEREADORES PARA NINGUEM PODER ACESSAR
}

void gravarVotosBinariosPrefeitos(int presentes, int votosPrefeito[]) {
    FILE *ponteiroArqBinarioP;
    ponteiroArqBinarioP = fopen("binario_prefeito.dat", "wb"); // CRIA UM ARQUIVO BINARIO PARA GUARDAR OS VOTOS EM PREFEITO

    if (ponteiroArqBinarioP == NULL)
        exit(1);

    fwrite(votosPrefeito, sizeof(int), presentes, ponteiroArqBinarioP); // TRANSFERE OS DADOS DO VETOR PARA O ARQUIVO BINARIO 

    fclose(ponteiroArqBinarioP);

    memset(votosPrefeito, 0, sizeof(int) * MAX); // ZERA O VETOR DE VOTOS EM PREFEITOS PARA NINGUEM PODER ACESSAR
}

void apuracaoVotosVereador(int apuracaoVereador[], int presentes, vereador listaVereador[], partidos listaPartidos[]) {
    FILE *ponteiroApuracao;
    ponteiroApuracao = fopen("binario_vereador.dat", "rb"); // ABRINDO PARA LEITURA O ARQUIVO BINARIO DE VEREADOR
    if (ponteiroApuracao == NULL)
        exit(1);

    fread(apuracaoVereador, sizeof(int), presentes, ponteiroApuracao); // JOGANDO PARA "apuracaoVereador" O CONTEUDO DO ARQUIVO BINARIO
    fclose(ponteiroApuracao);

    int nulos = 0; //CONTAGEM DE VOTOS NULOS EM VEREADORES
    int brancos = 0; //CONTAGEM DE VOTOS BRANCOS EM VEREADORES
    
    for (int i = 0; i < presentes; i++) { //APURAÇÃO DE VOTOS EM VEREADORES
        if (apuracaoVereador[i]==0){
            brancos++; // SE DIGITAR 0, O VOTO FOI BRANCO
        }else if(apuracaoVereador[i]==1){
            nulos++; // SE DIGITAR 1, O VOTO FOI NULO
        }else{
            for(int j = 0; j < 20; j++) { 
                if(apuracaoVereador[i]==listaVereador[j].numvoto){ // ENCONTRA EM QUAL VEREADOR O VOTO FOI COMPUTADO
                    listaVereador[j].votos++; // VOTO DO VEREADOR SOBE EM 1
                    }else if(apuracaoVereador[i]==listaPartidos[j].partido){ // ENCONTRA SE O VOTO FOI NO PARTIDO
                        listaPartidos[j].votos++; // VOTO DO PARTIDO SOBE EM 1
                    }}}}
    
    ponteiroApuracao = fopen("arquivoVotosVereadores.txt", "w"); // CRIANDO O ARQUIVO TXT DE VOTOS EM VEREADORES
    if (ponteiroApuracao == NULL)
        exit(1);

    fprintf(ponteiroApuracao, "Todos os votos em candidatos inexistentes foram retirados da lista. \n");
    fprintf(ponteiroApuracao, "Eleitores presentes: %d\n", presentes);
    fprintf(ponteiroApuracao, "Votos em branco: %d\n", brancos);
    fprintf(ponteiroApuracao, "Votos nulos: %d\n", nulos);
    
    for(int i=0; i<5;i++){
        if(listaPartidos[i].votos > 0){
             fprintf(ponteiroApuracao, "Partido %s, Digito %d, %d votos\n", listaPartidos[i].sigla, listaPartidos[i].partido,listaPartidos[i].votos);}}
    
    for(int i=0 ; i<20;i++){
        if(listaVereador[i].votos > 0){
            fprintf(ponteiroApuracao, "Vereador: %s, Partido: %s, %d votos\n", listaVereador[i].nome,listaVereador[i].sigla, listaVereador[i].votos);}}

    fclose(ponteiroApuracao);
}

void apuracaoVotosPrefeito(int apuracaoPrefeito[], int presentes, prefeito listaPrefeito[]) {
    FILE *ponteiroApuracao;
    ponteiroApuracao = fopen("binario_prefeito.dat", "rb"); // ABRINDO PARA LEITURA O ARQUIVO BINARIO DE PREFEITO
    if (ponteiroApuracao == NULL)
        exit(1);

    fread(apuracaoPrefeito, sizeof(int), presentes, ponteiroApuracao); // JOGANDO PARA "apuracaoPrefeito" O CONTEUDO DO ARQUIVO BINARIO
    fclose(ponteiroApuracao);

    int nulos = 0; // CONTAGEM DE VOTOS NULOS PARA PREFEITOS
    int brancos = 0; //CONTAGEM DE VOTOS BRANCOS PARA PREFEITOS

    for(int i = 0; i < presentes; i++){ //APURAÇÃO DE VOTOS EM PREFEITOS
        if(apuracaoPrefeito[i]==0){
            brancos++; // SE DIGITAR 0, O VOTO FOI BRANCO
        }else if(apuracaoPrefeito[i]==1){
            nulos++; // SE DIGITAR 1, O VOTO FOI NULO
        }else{
            for(int j = 0; j < 20; j++){ 
                if(apuracaoPrefeito[i]==listaPrefeito[j].num){ //ENCONTRA EM QUAL PREFEITO O VOTO FOI COMPUTADO
                    listaPrefeito[j].votos++; // VOTO DO PREFEITO SOBE EM 1
    }}}}

    ponteiroApuracao = fopen("arquivoVotosPrefeitos.txt", "w"); // CRIANDO O ARQUIVO TXT DE VOTOS EM PREFEITOS
    if (ponteiroApuracao == NULL)
        exit(1);

    fprintf(ponteiroApuracao, "Todos os votos em candidatos inexistentes foram retirados da lista. \n");
    fprintf(ponteiroApuracao, "Eleitores presentes: %d\n", presentes);
    fprintf(ponteiroApuracao, "Votos em branco: %d\n", brancos);
    fprintf(ponteiroApuracao, "Votos nulos: %d\n", nulos);

    for(int i=0 ; i<20;i++){
        if(listaPrefeito[i].votos > 0){
            fprintf(ponteiroApuracao, "Prefeito: %s, %d votos\n", listaPrefeito[i].nome,listaPrefeito[i].votos);}}

    fclose(ponteiroApuracao);
}

int main() {
    int select;
    int presentes = 0; // VARIAVEL PARA SABER O NUMERO DE ELEITORES PRESENTES NA VOTAÇÃO
    int dados = 0; // VARIAVEL PARA IDENTIFICAR SE OS DADOS DE ELEITORES, VEREADORES E PREFEITOS FORAM IMPORTADOS
    int vot = 0; // VARIAVEL PARA IDENTIFICAR SE A VOTAÇÃO TERMINOU
    int votosVereador[MAX];
    int votosPrefeito[MAX];
    int apuracaoVereador[MAX];
    int apuracaoPrefeito[MAX];

    do{
        system("cls");
        printf("1- Importar dados \n2- Iniciar votacao \n3- Apuracao dos votos \n4- Sair \n");
        scanf("%d", &select);

        switch(select){
            case 1:
                system("cls");
                registroVereadores(listaVereador); //REGISTRA OS VEREADORES A PARTIR DO ARQUIVO TXT
                registroPrefeitos(listaPrefeito); //REGISTRA OS PREFEITOS A PARTIR DO ARQUIVO TXT
                registroEleitores(listaEleitor); //REGISTRA OS ELEITORES A PARTIR DO ARQUIVO TXT
                registroPartidos(listaPartidos); //REGISTRA OS PARTIDOS MANUALMENTE
                printf("Dados importados com sucesso! \n");
                system("pause");
                system("cls");
                dados=1;
            break;

            case 2:
            if(vot==1){
                printf("A votacao esta encerrada \n");
            }
            else if(dados==1){
                votacao(listaEleitor, votosVereador, votosPrefeito, &presentes); // FAZ A VOTAÇÃO DOS CANDIDATOS
                gravarVotosBinariosVereadores(presentes, votosVereador); // GRAVA OS VOTOS EM VEREADORES NUM ARQUIVO BINARIO E APAGA OS VOTOS DA VARIAVEL
                gravarVotosBinariosPrefeitos(presentes, votosPrefeito); // GRAVA OS VOTOS EM PREFEITOS NUM AQRUIVO BINARIO E APAGA OS VOTOS DA VARIAVEL
                vot=1;
            }else{
                printf("Nao ha dados ainda. \n");}
                system("pause");
            break;

            case 3:
            if(vot==1){
                apuracaoVotosVereador(apuracaoVereador, presentes, listaVereador, listaPartidos); // LE O ARQUIVO BINARIO E FAZ A CONTAGEM DOS VOTOS EM CADA VEREADOR, TANTO COMO VOTOS NOS PARTIDOS, BRANCOS E NULOS, E POR FIM FAZ UM RELATORIO EM ARQUIVO TXT
                apuracaoVotosPrefeito(apuracaoPrefeito, presentes, listaPrefeito); // LE O ARQUIVO BINARIO E FAZ A CONTAGEM DOS VOTOS EM CADA PREFEITO, TANTO COMO VOTOS EM BRANCO E NULOS, E POR FIM FAZ UM RELATORIO EM ARQUIVO TXT
            }else{
                printf("A votacao nao foi realizada. \n");}
                system("pause");
            break;
        }
    }while(select!=4);
   
    return 0;
}
