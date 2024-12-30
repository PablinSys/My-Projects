// See https://aka.ms/new-console-template for more information
using SFML.Window;
using GAME_LIFE.src;

public class Program 
{
    public static void Main(string[] args)
    {
        Console.WriteLine("Jogo da Vida");
        //GAME_LIFE.tests.TabelaGrids.Run();
        var Simulador = new Simulador(new VideoMode(2000, 900), 20);
        Simulador.Inicializar();
    }
}
