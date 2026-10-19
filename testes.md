# Planejamento de Testes para validação do código:

O código basicamente opera acendendo e apagando dois leds, portanto
o jeito mais prático de validar seu funcionamento é:

- [ ] Desative um dos "gpio_pin_set_dt(&led_, 1)" que está dentro dos if. Dessa forma é possível checar se o outro led está funcionando corretamente e até, por video, estimar seu tempo de blink. Além de  ser possível notar se não há interferência na execução das threads.
- [ ] Reative o primeiro e desative o outro led e faça a mesma checagem. A certeza é que o intervalo entre cada blink deverá ser maior ou menor dependendo de qual foi desativado.
- [ ] Ative ambos e veja se piscam em frequências diferentes, dado que é difícil estimar o tempo exato deles (ainda mais que 350 não é multíplo de 1000). Veja se o tempo não altera ao longo do funcionamento.
- [ ] OPCIONAL: altere a duração do msleep de qualquer um dos dois. É possível apenas testar isso ou até mesmo checar o tempo em que o led fica acesso.