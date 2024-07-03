O código começa com um switch em que o usuário poderá transferir os dados dos eleitores, vereadores e prefeitos para a urna. O arquivo dos eleitores contém: Nome, titulo, deficiência e comparecimento. O arquivo dos vereadores possui: Nome, identificação do vereador, numero do partido, sigla do partido e numero do vereador. O arquivo dos prefeitos possui: Nome, numero dos prefeitos, sigla do partido.

Os arquivos .txt com esses dados estão na pasta "output".

Após isso e apenas após isso, o usuário poderia iniciar a votação.

Não dei uma opção para encerrar a votação antes de todos os eleitores votarem pois no arquivo .txt de eleitores, eles possuem uma identificação S ou N, de caso foram votar, ou não. E por esse motivo, todos os eleitores que compareceram a votação, PRECISAM votar para a eleição se encerrar, caso contrario não haveria necessidade dessa variável "S ou N".

A cada voto computado, o programa os embaralha numa variável.

Apenas após o ultimo eleitor elegível (os que tinham "S" no documento .txt), votar, a votação se encerra, um arquivo binário com os votos é criado, e a variável que contém os votos é apagada para que não haja a possibilidade de alguém ver os votos através do programa.

Não é possível começar a votação novamente.

Após a votação e apenas após ela se encerrar, podemos criar o relatório .txt, que lê o arquivo binário e o organiza, juntando os votos e identificando quem são os correspondentes.

-----------------------------------------------------------------------------------------------------------------------------------------

Para testar o código, deixei apenas 10 eleitores, e apenas um dos 10 não compareceu a votação.

É necessário digitar os títulos "10001 a 10009", em qualquer ordem, para a votação ser concluida.

Os relatórios e os arquivos binários serão gerados na pasta "output".

Votos "errados" serão excluídos do relatório e só é possível identifica-los se subtrairmos o numero presente de eleitores aos votos computados corretamente.
