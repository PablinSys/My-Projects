using SFML.Graphics;
using SFML.System;
using SFML.Window;

namespace GAME_LIFE.src
{
    public partial class Celula
    {
        public static explicit operator VertexArray(Celula c)
        {
            return new VertexArray(PrimitiveType.Quads, 4)
            {
                [0] = new Vertex(new Vector2f(c.pos_x, c.pos_y), Color.White),
                [1] = new Vertex(new Vector2f(c.pos_x + c.space, c.pos_y), Color.White),
                [2] = new Vertex(new Vector2f(c.pos_x + c.space, c.pos_y + c.space), Color.White),
                [3] = new Vertex(new Vector2f(c.pos_x, c.pos_y + c.space), Color.White)
            };
        }
    }
    public struct GradesCount
    {
        public int X { get; set; }
        public int Y { get; set; }
    }
    public class Simulador
    {
        private readonly SortedSet<Celula> celulas = new SortedSet<Celula>(Comparer<Celula>.Create((x, y) => {
            return x.pos_y != y.pos_y ? 
                x.pos_y.CompareTo(y.pos_y) : 
                x.pos_x.CompareTo(y.pos_x);
        }));
        private readonly GradesCount gradesCount;
        private readonly RenderWindow window;
        private VertexArray[] ambiente;
        private readonly int spacing;
        public Simulador(VideoMode tela, int espaçamento)
        {
            spacing = espaçamento;
            window = new RenderWindow(tela, "Jogo da Vida");
            gradesCount = new GradesCount(){X = (int)(window.Size.X/spacing), Y = (int)(window.Size.Y/spacing)};
            window.Closed += (s, e) => window.Close();
            // window.KeyPressed += (s, e) =>
            // {
            //     var currentwindow = (RenderWindow?)s;
            //     if (e.Code == Keyboard.Key.Escape)
            //         currentwindow?.Close();
            // };
            window.MouseButtonPressed += OnMouseButtonClick;
        }
        public bool Inicializar()
        {
            bool pause = true;
            if (ambiente is null) ambiente = CriarAmbiente();
            while (window.IsOpen)
            {
                window.DispatchEvents();
                Exibir();
                while (!Keyboard.IsKeyPressed(Keyboard.Key.Enter) && pause)
                {
                    window.DispatchEvents();
                    while (Mouse.IsButtonPressed(Mouse.Button.Left) || Mouse.IsButtonPressed(Mouse.Button.Right)) 
                    {
                        OnMouseButtonClick(null, new MouseButtonEventArgs(new MouseButtonEvent(){
                            Button = Mouse.IsButtonPressed(Mouse.Button.Left) ? Mouse.Button.Left : Mouse.Button.Right
                        }));
                        Thread.Sleep(100);
                    }
                }
                if (pause) pause = false;
                if (Keyboard.IsKeyPressed(Keyboard.Key.Escape)) 
                {
                    Thread.Sleep(500);
                    break;
                }
                //Console.WriteLine($"[{string.Join(", ", celulas.Select(c => "(" + c.pos_x/c.space + "," + c.pos_y/c.space + ")"))}]");
                Thread.Sleep(100);
                Evoluir();
            }
            Inicializar();
            return true;
        }
        private VertexArray[] CriarAmbiente()
        {
            int tamanho = gradesCount.X + gradesCount.Y;
            VertexArray[] grades = new VertexArray[tamanho];
            for (int i = 0; i < tamanho; i++)
            {
                grades[i] = new VertexArray(PrimitiveType.Lines, 2);
                if (i >= gradesCount.X)
                {
                    grades[i][0] = new Vertex(new Vector2f(1, (i-gradesCount.X+1)*spacing), Color.White);
                    grades[i][1] = new Vertex(new Vector2f(window.Size.X, (i-gradesCount.X+1)*spacing), Color.White);
                }
                else
                {
                    grades[i][0] = new Vertex(new Vector2f((i+1)*spacing, 1), Color.White);
                    grades[i][1] = new Vertex(new Vector2f((i+1)*spacing, window.Size.Y), Color.White);
                }
            }
            return grades;
        }
        private void Exibir()
        {
            window.Clear();
            foreach (var ambienteCell in ambiente) 
            {
                window.Draw(ambienteCell);
            }
            foreach (var cell in celulas) window.Draw((VertexArray)cell);
            window.Display();
        }
        private void Evoluir()
        {
            try
            {
                int firstCellPos = celulas.First().pos_y/spacing, lastCellPos = celulas.Last().pos_y/spacing;
                List<Celula> newCells = new List<Celula>();
                List<Celula> deadCells = new List<Celula>();
                for (int i = firstCellPos -1 < 0 ? 0 : firstCellPos-1; i < ((lastCellPos + 2) > gradesCount.Y ? gradesCount.Y : lastCellPos+2); i++)
                    for (int j = 0; j < gradesCount.X; j++)
                    {
                        var cell = new Celula(j*spacing, i*spacing, spacing);
                        if (!celulas.Contains(cell)) cell.vivo = false;
                        int vizinhosQtd = CellsCount(new Vector2f(cell.x, cell.y));

                        // 1-Toda célula morta com exatamente três vizinhos vivos torna-se viva (nascimento).
                        // 2-Toda célula viva com menos de dois vizinhos vivos morre por isolamento.
                        // 3-Toda célula viva com mais de três vizinhos vivos morre por superpopulação.
                        // 4-Toda célula viva com dois ou três vizinhos vivos permanece viva.
                        if (!cell.vivo && vizinhosQtd == 3) newCells.Add(cell);
                        else if (cell.vivo && (vizinhosQtd < 2 || vizinhosQtd > 3)) deadCells.Add(cell);
                    }
                foreach (var cell in newCells) celulas.Add(cell);
                foreach (var cell in deadCells) celulas.Remove(cell);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }
        private int CellsCount(Vector2f cell_pos)
        {
            int count = 0, pos_h = (int)(cell_pos.X/spacing), pos_v = (int)(cell_pos.Y/spacing);
            Celula cellFind;
            // Verifição vertical
            if (pos_v-1 >= 0)
            {
                cellFind = new Celula((int)cell_pos.X, (pos_v-1)*spacing, spacing);
                count += celulas.Count(cell => cell == cellFind);
            }
            if (pos_v + 1 < gradesCount.Y)
            {
                cellFind = new Celula((int)cell_pos.X, (pos_v+1)*spacing, spacing);
                count += celulas.Count(cell => cell == cellFind);
            }
            // Verificação na diagonal
            if (pos_v - 1 >= 0 && pos_h - 1 >= 0)
            {
                cellFind = new Celula((pos_h-1)*spacing, (pos_v-1)*spacing, spacing);
                count += celulas.Count(cell => cell == cellFind);
            }
            if (pos_h + 1 < gradesCount.X && pos_v + 1 < gradesCount.Y)
            {
                cellFind = new Celula((pos_h+1)*spacing, (pos_v+1)*spacing, spacing);
                count += celulas.Count(cell => cell == cellFind);
            }
            if (pos_v - 1 >= 0 && pos_h + 1 < gradesCount.X)
            {
                cellFind = new Celula((pos_h+1)*spacing, (pos_v-1)*spacing, spacing);
                count += celulas.Count(cell => cell == cellFind);
            }
            if (pos_v + 1 < gradesCount.Y && pos_h - 1 >= 0)
            {
                cellFind = new Celula((pos_h-1)*spacing, (pos_v+1)*spacing, spacing);
                count += celulas.Count(cell => cell == cellFind);
            }
            // Verificação horizontal
            if (pos_h-1 >= 0)
            {
                cellFind = new Celula((pos_h-1)*spacing, (int)cell_pos.Y, spacing);
                count += celulas.Count(cell => cell == cellFind);
            }
            if (pos_h + 1 < gradesCount.X)
            {
                cellFind = new Celula((pos_h+1)*spacing, (int)cell_pos.Y, spacing);
                count += celulas.Count(cell => cell == cellFind);
            }
            return count;
        }
        private void OnMouseButtonClick(object? sender, MouseButtonEventArgs e)
        {
            var mouse = Mouse.GetPosition(window);
            if (mouse.X < 0 || mouse.Y < 0) return;
            else
            {
                var celula = new Celula(mouse.X, mouse.Y, spacing);

                if (e.Button == Mouse.Button.Left) celulas.Add(celula);
                // else 
                // {
                //     int index = -1;
                //     for (int i = 0; i < celulas.Count; i++) 
                //     {
                //         if (((VertexArray)celulas.ElementAt(i)).Equals((VertexArray)celula)) 
                //         {
                //             index = i;
                //             break;
                //         }
                //     }
                //     if (index != -1) celulas.Remove(celulas.ElementAt(index));
                // }
            }
            Exibir();
        }
    }
}