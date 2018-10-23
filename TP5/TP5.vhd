library ieee, myLibrary;
use ieee.std_logic_1164.all;
use myLibrary.felipe.all;

entity TP5 is
	port (
		start: in std_logic;
		stop: in std_logic;
		rst: in std_logic;
		clk_placa: in std_logic;
		displaya: out std_logic_vector(6 downto 0);
		displayb: out std_logic_vector(6 downto 0)
	);
end TP5;

architecture TP5_arq of TP5 is

component maquina is
	port (
		start: in std_logic;
		stop:  in std_logic;
		reset: in std_logic;
		clk:	 in std_logic;
		state: inout estado:= inicial;
		cont:  out natural := 0
	);
end component


component divisor_clock is
	port (
		clock50: in std_logic;
		clock_1: buffer std_logic
	);
end component;

component decodificador_dec_7_seg is
	port (
		display_dec: in natural;
		display1: out std_logic_vector (6 downto 0);
		display2: out std_logic_vector (6 downto 0);
	);
end component;


signal clk: std_logic;
signal stat: estado:=inicial
signal contagem: natural:=0;

begin

	divisor_clock_aula: divisor_clock port map (clk_placa, clk);
	maquina_aula: maquina port map (start, stop, rst, clk, stat, contagem);
	decoder_display_aula: decodificador_dec_7_seg port map(contagem, displaya, displayb);

end TP5_arq;