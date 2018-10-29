library ieee, myLibrary;
use ieee.std_logic_1164.all;
use myLibrary.felipe.all;

entity maquina is
	port (
		start: 						 in std_logic;
		reset: 						 in std_logic;
		clk:	 						 in std_logic;
		state: 						 inout estado:= inicial;
		cont:  						 out natural := 0;
		sinalVermelhoV:			 out std_logic;
		sinalAmareloV: 			 out std_logic;
		sinalVerdeV: 			    buffer std_logic;
		sinalVermelhoP: 			 out std_logic;
		sinalVerdeP: 			    buffer std_logic
	);
end maquina;

architecture maquina_arq of maquina is

signal aux: natural :=0;

begin	
	process(start, reset, clk) is
		begin
			if reset = '0' then
				state <= inicial;
				aux <= 0;
			elsif state = inicial then
				sinalVermelhoV <= '1'; --Estado inicial dos semaforos
				sinalAmareloV  <= '1';
				sinalVerdeV    <= '0';
				sinalVermelhoP <= '0';
				sinalVerdeP    <= '1';
				if (start'event and start = '0') then
					state <= espera;
				end if;
				aux <= 0;
			elsif state = espera then
				state <= piscaVerdeVec;								
			elsif state = piscaVerdeVec then
				sinalVerdeV <= not sinalVerdeV;
				sinalVerdeV <= not sinalVerdeV;
				sinalVerdeV <= not sinalVerdeV;
				state <= luzAmarelaVec;
				aux <= 0;
			elsif state = luzAmarelaVec then
				sinalVermelhoV <= '1'; 
				sinalAmareloV  <= '0';
				sinalVerdeV    <= '1';
				sinalVermelhoP <= '0';
				sinalVerdeP    <= '1';
				state <= luzVermelhaVec;
				aux <= 0;
			elsif state = luzVermelhaVec then
				sinalVermelhoV <= '0'; 
				sinalAmareloV  <= '1';
				sinalVerdeV    <= '1';
				sinalVermelhoP <= '0';
				sinalVerdeP    <= '1';
				state <= atravessa;
				aux <= 0;
			elsif state = atravessa then
				sinalVermelhoV <= '0'; 
				sinalAmareloV  <= '1';
				sinalVerdeV    <= '1';
				sinalVermelhoP <= '1';
				sinalVerdeP    <= '0';
				state <= piscaVerdePed;
				aux <= 0;
			elsif state = piscaVerdeVec then
				sinalVerdeP <= not sinalVerdeP;
				sinalVerdeP <= not sinalVerdeP;
				sinalVerdeP <= not sinalVerdeP;
				state <= luzVermelhaPed;
				aux <= 0;
			elsif state = luzVermelhaPed then
				sinalVermelhoV <= '0'; 
				sinalAmareloV  <= '1';
				sinalVerdeV    <= '1';
				sinalVermelhoP <= '0';
				sinalVerdeP    <= '1';
				state <= inicial;
				aux <= 0;
			elsif (clk'event and clk = '1') then
					if aux < 3 then
						aux <= aux + 1;
					end if;
			end if;
	end process;
	cont <= aux;
end maquina_arq;