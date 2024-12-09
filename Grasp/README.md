# 🎒 Implementação da Metaheurística GRASP para o Problema da Mochila com Bônus (QKP)  

Este repositório contém a implementação da metaheurística **GRASP (Greedy Randomized Adaptive Search Procedure)** para resolver o **Problema da Mochila com Bônus (QKP)**.  

### Detalhes do problema:
O **QKP** é uma extensão do clássico problema da mochila, onde:  
- Há bônus associados à seleção simultânea de pares de itens.  
- O objetivo é maximizar a soma dos valores dos itens e dos bônus, respeitando a capacidade da mochila.  

### Informações adicionais:
- **Instância do problema:** [Formato das Instâncias QKP](https://cedric.cnam.fr/~soutif/QKP/format.html).  
- Implementado em **C**, com foco na eficiência e qualidade da solução.  

### Principais características da solução:
- **Construção da solução inicial:** Estratégia gulosa randomizada com adaptação baseada na função alpha.  
- **Melhoria local:** Refinamento para maximizar o valor total da solução encontrada.  

Este repositório é ideal para estudos de otimização combinatória e aplicações práticas da metaheurística GRASP.  
