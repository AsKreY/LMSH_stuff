150553877 --- номер посылки в cf

Заметим, что если после n действий нужная карта в середине с веряотностью t, то на следующем действии она будет в центре с вероятностью 1/2(1-t) (так как может прийти только из краёв). Если создать реккурентную последовательность для вероятности нахождения карты в центре, то она будет выглядеть так: t_n=1/2(1-t_{n-1}). Тогда мы легко можем посчитать общую формулу для n-го члена, которую мы и используем в последовательности