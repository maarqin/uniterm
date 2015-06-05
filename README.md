# Uniterm
###Implementação de um Terminal de Linha de Comando

#### Introdução
Neste trabalho, implementaremos um Terminal de Linha de Comando para o Linux,
nos moldes do bash, tcsh, fish, zsh, cmd.exe, PowerShell, dentre tantos outros. Obviamente
a nossa versão será mais simples, porém completamente funcional para atividades básicas
como: verificar o relógio; navegar e manipular o sistema de arquivos; lançar novos processos
rodando outros programas.
O objetivo deste trabalho é nos aproximarmos ainda mais das camadas mais rasas de
um sistema operacional, pois as linguagens que utilizamos no aprendizado de programação
vêm com vastas bibliotecas que facilitam toda sorte de trabalho. Isso é uma coisa boa,
porém esconde os detalhes de operação dos próprios sistemas operacionais. Como estamos
estudando justamente essa classe de sistemas, é interessante sabermos como um programa
se comunica diretamente com eles, e quais tipos de serviços eles nos oferecem.
Neste caso, vamos conhecer as principais chamadas de sistema oferecidas pelo padrão POSIX,
seguida por quase todos os sistemas operacionais UNIX, e muitos outros, até mesmo o
Windows. Como todo sistema operacional que implementa o POSIX tem suas próprias chamadas
de sistema únicas, iremos verificaremos também algumas outras chamadas específicas
para o Linux, conhecidas como Linux Standard Base (LSB).
Assim como o trabalho do bimestre passado, este é um trabalho investigativo e de conteúdo
extra-aula, o que significa que sem pesquisa e leitura a livros e documentos da Internet,
não será possível fazê-lo. Significa também que quem deixar para a última hora não terá
tempo hábil para fazê-lo.
