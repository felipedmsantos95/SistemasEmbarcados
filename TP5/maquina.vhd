library ieee, myLibrary;
use ieee.std_logic_1164.all;
use myLibrary.felipe.all;

entity maquina is
	port (
		start: in std_logic;
		stop:  in std_logic;
		reset: in std_logic;
		clk:	 in std_logic;
		state: inout estado:= inicial;
		cont:  out natural := 0
	
	);
end maquina;

architecture maquina_arq of maquina is
signal aux: natural :=0;
begin
	process(start, reset, clk, stop) is
		begin
			if reset = '0' then
				state <= inicial;
				aux <= 0;
			elsif state = inicial then
				if (start'event and start = '0') then
					state <= contagem;
				end if;
			elsif (clk'event and clk = '1') then
				if aux < 15 then
					aux <= aux + 1;
				end if;
			end if;
	end process;
	cont <= aux;
end maquina_arc;