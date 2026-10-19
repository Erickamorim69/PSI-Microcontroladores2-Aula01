# Planejamento de Testes para validação do código:

O código basicamente opera acendendo e apagando dois leds, portanto
o jeito mais prático de validar seu funcionamento é:

- [ ] Desative um dos "gpio_pin_set_dt(&led_, 1)" que está dentro dos if. Dessa forma é possível checar se o outro led está funcionando corretamente e até, por video, estimar seu tempo de blink.
- [ ] Reative o primeiro e desative o outro led e faça a mesma checagem. A certeza é que o intervalo entre cada blink deverá ser maior ou menor dependendo de qual foi desativado.
- [ ] Ative ambos e veja se piscam em frequências diferentes, dado que é difícil estimar o tempo exato deles (ainda mais que 350 não é multíplo de 1000).
- [ ] OPCIONAL: altere a validação if(cont % __ == 0) de qualquer um dos dois. O led só acenderá nos multíplos do valor escrito após o "%". Portanto, o contador soma a cada 50ms, se o número for 10, ele piscará a cada 10 x 50 = 500ms.