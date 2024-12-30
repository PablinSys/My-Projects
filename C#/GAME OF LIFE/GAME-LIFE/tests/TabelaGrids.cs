
using SFML.Graphics;
using SFML.Window;
using SFML.System;
using System.Runtime.Serialization;

namespace GAME_LIFE.tests
{
    public class TabelaGrids
    {
        public static VertexArray AddLifesToGrid(Vector2f pos, int espaçamento, int qtdGradesX, int qtdGradesY)
        {
                VertexArray vertexArray = new VertexArray(PrimitiveType.TriangleStrip, 6);
                Vertex vertex = vertexArray[0];
                var position = GetPositionMouseToGrid(pos, espaçamento, qtdGradesX, qtdGradesY);
                float pos_x = position.X, pos_y = position.Y;
                vertex.Position = new Vector2f(pos_x-espaçamento, pos_y-espaçamento);
                vertexArray[0] = vertex;
                vertexArray[4] = vertex;
                vertex.Position = new Vector2f(pos_x, pos_y);
                vertexArray[5] = vertex; 
                vertexArray[2] = vertex;
                vertex.Position = new Vector2f(pos_x, pos_y-espaçamento);
                vertexArray[1] = vertex;
                vertex.Position = new Vector2f(pos_x-espaçamento, pos_y);
                vertexArray[3] = vertex;
                return vertexArray;
        } 
        public static Vector2f GetPositionMouseToGrid(Vector2f mousePos, int espaçamento, int qtdGradesX, int qtdGradesY)
        {
            float pos_x = (int)(mousePos.X/espaçamento)*espaçamento + espaçamento, pos_y = (int)(mousePos.Y/espaçamento)*espaçamento + espaçamento;
            // for (int i = (int)(mousePos.X/espaçamento); i <= qtdGradesX; i++) 
            // {
            //     if (mousePos.X/(i*espaçamento) < 1) 
            //     {
            //         pos_x = i*espaçamento;
            //         break; 
            //     }
            // }
            // repetition = 0;
            // for (int i = (int)(mousePos.Y/espaçamento); i <= qtdGradesY; i++)
            // {
            //     if (mousePos.Y/(i*espaçamento) < 1) 
            //     {
            //         pos_y = i*espaçamento;
            //         break;
            //     }
            // }
            return new Vector2f(pos_x, pos_y);
        }
        public static void Run()
        {
            var window = new RenderWindow(new VideoMode(1000, 800), "Tabela Grids");
            
            window.Closed += (s, e) => ((RenderWindow?)s)?.Close();
            window.KeyPressed += (s, e) =>
            {
                var window = (RenderWindow?)s;
                if (e.Code == Keyboard.Key.Escape)
                    window?.Close();
            };
            int espaçamento = 50;
            int width_lines= 1;
            int qtdGradesX = 0, qtdGradesY = 0;
            VertexArray[] vertices = new VertexArray[1];
            List<VertexArray> lifes = new List<VertexArray>();

            Func<uint, uint, bool> resize = (newWidth, newHeight) =>
            {
                qtdGradesX = (int)(newWidth / espaçamento) + width_lines;
                qtdGradesY = (int)(newHeight / espaçamento) + width_lines;

                vertices = new VertexArray[(int)qtdGradesX + (int)qtdGradesY];
                try
                {
                    for (int i = 0; i < vertices.Length; i++)
                    {
                        for (int j = 0; j < width_lines; j++) 
                        {
                            if (i >= qtdGradesX)
                            {
                                vertices[i] = new VertexArray(PrimitiveType.Lines, 2);
                                vertices[i][0] = new Vertex(new Vector2f(1, (i-qtdGradesX+1)*espaçamento + j), Color.White);
                                vertices[i][1] = new Vertex(new Vector2f(window.Size.X, (i-qtdGradesX+1)*espaçamento + j), Color.White);
                            }
                            else
                            {
                                vertices[i] = new VertexArray(PrimitiveType.Lines, 2);
                                vertices[i][0] = new Vertex(new Vector2f((i+1)*espaçamento + j, 1), Color.White);
                                vertices[i][1] = new Vertex(new Vector2f((i+1)*espaçamento + j, window.Size.Y), Color.White);
                            }
                        }
                    }
                }
                catch (Exception) { return false; }
                return true;
            };
            Func<VertexArray[], bool> draw = (vertices) => 
            {
                for (int i = 0; i < vertices.Length; i++)
                {
                    window.Draw(vertices[i]);
                }
                foreach (var points in lifes) window.Draw(points);
                return true;
            };
            //window.Resized += (s, e) => resize(e.Width, e.Height);
            window.MouseButtonPressed += (sender, e) =>
            {
                if (sender is RenderWindow window) 
                {
                    if (e.Button == Mouse.Button.Left)
                    {
                        var life = AddLifesToGrid(new Vector2f(e.X, e.Y), espaçamento, qtdGradesX, qtdGradesY);
                        Console.WriteLine($"mouse position: {e.X}, {e.Y}");
                        Console.WriteLine($"position in grid: {GetPositionMouseToGrid(new Vector2f(e.X, e.Y), espaçamento, qtdGradesX, qtdGradesY)}");
                        
                        if (!lifes.Exists(x => x[2].Position == life[2].Position)) lifes.Add(life);                     
                        window.Draw(life);
                        //window.Draw(lifes[lifes.Count - 1])
                    }
                    else if (e.Button == Mouse.Button.Right)
                    {
                        var position = GetPositionMouseToGrid((Vector2f)Mouse.GetPosition(window), espaçamento, qtdGradesX, qtdGradesY);
                        int index = lifes.FindIndex(x => x[2].Position == position);
                        if (index != -1)
                        {
                            lifes.RemoveAt(index);
                            window.Clear(Color.Black);
                        } 
                        //draw(vertices);
                        //window.Display();
                    }
                }
            };
            resize(window.Size.X, window.Size.Y);
            while (window.IsOpen)
            {
                window.Clear(Color.Black);
                window.DispatchEvents();
                if (!draw(vertices))
                {
                    Console.WriteLine("OCORREU UM ERRO AO DESENHAR AS GRADES");
                    window.Close();
                }
                while (Mouse.IsButtonPressed(Mouse.Button.Left))
                {
                    var life = AddLifesToGrid((Vector2f)Mouse.GetPosition(window), espaçamento, qtdGradesX, qtdGradesY);
                    if (!lifes.Exists(x => x[2].Position == life[2].Position)) lifes.Add(life);
                    window.Draw(life);
                    window.Display();
                }
                while (Mouse.IsButtonPressed(Mouse.Button.Right))
                {
                    var position = GetPositionMouseToGrid((Vector2f)Mouse.GetPosition(window), espaçamento, qtdGradesX, qtdGradesY);
                    int index = lifes.FindIndex(x => x[2].Position == position);
                    if (index != -1)
                    {
                        lifes.RemoveAt(index);
                        window.Clear(Color.Black);
                        draw(vertices);
                        window.Display();
                    }                    
                }
                window.Display();
                Thread.Sleep(1000);
            }
        }
    }
}