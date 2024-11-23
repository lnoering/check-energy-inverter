<h3 align="center">Verificando se a energia vem do Inversor de Frequência/Checking if power comes from the Frequency Inverter</h1>
<p align="center">
    <img alt="logo" class="avatar rounded-2" height="60" src="/icon.png" width="60">
</p>
<p align="center">
    <a href="https://travis-ci.org/lnoering/check-energy-inverter">
        <img src="https://travis-ci.org/lnoering/check-energy-inverter.svg?branch=master" alt="Build Status">
    </a>
</p>


### Plataforma/Platform
    - Arduino Uno

### Ferramentas/Tools
<div class="snippet-clipboard-content notranslate position-relative overflow-auto">
<pre class="notranslate">
<code>
- IDE <a href="https://code.visualstudio.com/">Visual Studio Code</a> // 1.71.2
- IDE Extension <a href="https://platformio.org/">PlatformIO</a> // Core 6.1.5 Home 3.4.3
- Libraries <a href="https://github.com/lnoering/check-energy-inverter/blob/master/platformio.ini">Libs</a>
</code>
</Pre>
</div>

### Objetivo/Objective
    Verificar se a energia elétrica é proveniente da energia solar (com base na onda do inversor)
    /
    Checking the energy power is from solar energy (based on frequency inverter)


### Funcionalidades
    > Com base no interrupt externo ele conta o tempo que demora para cada ciclo, sabendo assim qual a frequência que está na rede.
        - O total de contagens que acontece para cada frequência desejada é definido no código. (main.h)


### IO
    Obs.: PINOS conforme a placa do arduino.
    - LED 
        - PINO (4) - PD4
    - Detect Zero Cross
        - PINO (2) - PD2

### Menu
    - Não tem menu.

### Lista de melhorias
    - Criar um circuito para inserir um sinal na onda elétrica, e fazer com que ele ligue conforme aciona o inversor. Com base nesse sinal teriamos 100% de certeza que o sinal é do inversor e não teria falhas,

### Bugs
    - Por ficar olhando a frequência e a diferença do inversor ser muito pouca da rede elétrica, pode acontecer dele não detectar 100%