library ieee;
use ieee.std_logic_1164.all;

entity divisor_clock is
	port (
		clock50: in std_logic;
		clock_1: buffer std_logic
	);
end divisor_clock;

architecture divisor_clock_arq of divisor_clock is
	signal contagem: natural :=0;
begin
	process(clock50)
	begin
		if(rising_edge(clock50)) then
			contagem <= contagem + 1;
			if(contagem = 500000000) then
				contagem <= 0;
				clock_1 <= not clock_1;
			end if;
		end if;
	end process;
end divisor_clock_arq;