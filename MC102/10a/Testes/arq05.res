A criacao do Linux
Em 1991, Linus Torvalds comecou o projeto que mais tarde se tornaria o nucleo Linux. Era inicialmente um emulador de terminal, o qual Torvalds usava para acessar os grandes servidores UNIX da universidade. Ele escreveu um programa especificamente para o hardware que estava usando e independente de um sistema operacional porque queria usar as funcoes de seu novo computador com um processador 80386.
O desenvolvimento foi feito no MINIX usando o GNU C compiler, o qual e ainda hoje a escolha principal para compilar o Linux (embora o codigo possa ser construido com outros compiladores, como o Intel C Compiler).
Como Torvalds escreveu no seu livro Just for Fun,9 ele eventualmente notou que havia escrito o nucleo de um sistema operacional. No dia 25 de agosto de 1991, ele anunciou esse sistema em um post no "comp.os.minix." da Usenet:10
    Ola a todos que estao usando minix -
    Eu estou fazendo um sistema operacional livre (e apenas um hobby, nao sera grande e profissional como o gnu) para os clones AT 386(486). Esta sendo desenvolvido desde abril e esta quase pronto. Gostaria de receber qualquer retorno sobre o que as pessoas gostam/nao gostam no minix, uma vez que o meu SO se parece um pouco com ele (mesmo layout fisico de sistema de arquivos (devido a razoes praticas) entre outras coisas.
    No momento eu o portei para bash(1.08) e gcc(1.40), e as coisas parecem funcionar. Isso implica que irei conseguir algo pratico dentro de poucos meses e gostaria de saber quais caracteristicas a maioria das pessoas gostaria que tivesse. Quaisquer sugestoes sao bem-vindas, mas nao prometo que eu va implementa-las :-)
    Linus
    PS. Sim — ele nao tem nenhum codigo minix, e possui um fs multitarefa. Ele NAO e portavel (usa troca de contexto 386, etc), e provavelmente nunca sera compativel com nada alem de discos rigidos AT, uma vez que isso e tudo o que eu tenho :-(.
    —Linus Torvalds
