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
			elsif state = espera then
				if (clk'event and clk = '1') then
					if aux < 3 then
						aux <= aux + 1;
					elsif aux = 3 then
						aux <= 0;
						state <= piscaVerdeVec;					
					end if;
				end if;					
			elsif state = piscaVerdeVec then
				if (clk'event and clk = '1') then
					sinalVerdeV <= not sinalVerdeV;
					sinalVerdeV <= not sinalVerdeV;
					sinalVerdeV <= not sinalVerdeV;
					if aux < 3 then
						aux <= aux + 1;
					elsif aux = 3 then
						aux <= 0;
						state <= luzAmarelaVec;					
					end if;
				end if;
			elsif state = luzAmarelaVec then
				sinalVermelhoV <= '1'; 
				sinalAmareloV  <= '0';
				sinalVerdeV    <= '1';
				sinalVermelhoP <= '0';
				sinalVerdeP    <= '1';
				if (clk'event and clk = '1') then
					if aux < 3 then
						aux <= aux + 1;
					elsif aux = 3 then
						aux <= 0;
						state <= luzVermelhaVec;					
					end if;
				end if;
			elsif state = luzVermelhaVec then
				sinalVermelhoV <= '0'; 
				sinalAmareloV  <= '1';
				sinalVerdeV    <= '1';
				sinalVermelhoP <= '0';
				sinalVerdeP    <= '1';
				if (clk'event and clk = '1') then
					if aux < 3 then
						aux <= aux + 1;
					elsif aux = 3 then
						aux <= 0;
						state <= atravessa;					
					end if;
				end if;
			elsif state = atravessa then
				sinalVermelhoV <= '0'; 
				sinalAmareloV  <= '1';
				sinalVerdeV    <= '1';
				sinalVermelhoP <= '1';
				sinalVerdeP    <= '0';
				if (clk'event and clk = '1') then
					if aux < 3 then
						aux <= aux + 1;
					elsif aux = 3 then
						aux <= 0;
						state <= piscaVerdePed;					
					end if;
				end if;
			elsif state = piscaVerdeVec then
				if (clk'event and clk = '1') then
					sinalVerdeP <= not sinalVerdeP;
					sinalVerdeP <= not sinalVerdeP;
					sinalVerdeP <= not sinalVerdeP;
					if aux < 3 then
						aux <= aux + 1;
					elsif aux = 3 then
						aux <= 0;
						state <= luzVermelhaPed;					
					end if;
				end if;
			elsif state = luzVermelhaPed then
				sinalVermelhoV <= '0'; 
				sinalAmareloV  <= '1';
				sinalVerdeV    <= '1';
				sinalVermelhoP <= '0';
				sinalVerdeP    <= '1';
				if (clk'event and clk = '1') then
					if aux < 3 then
						aux <= aux + 1;
					elsif aux = 3 then
						aux <= 0;
						state <= inicial;					
					end if;
				end if;
			end if;
	end process;
	cont <= aux;
end maquina_arq;