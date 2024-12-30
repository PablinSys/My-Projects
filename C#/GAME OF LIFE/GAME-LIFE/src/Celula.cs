namespace GAME_LIFE.src
{
    public partial class Celula
    {
        public float x { get; set; } = 0;
        public float y { get; set; } = 0;
        public int pos_x { get; private set;}
        public int pos_y { get; private set;}
        public int space { get; set; } = 0;
        public bool vivo { get; set; } = true;
        /// <summary>
        /// Cria uma nova Celula com as coordenadas X e Y.
        /// </summary>
        /// <param name="x">Coordenada X da celula.</param>
        /// <param name="y">Coordenada Y da celula.</param>
        public Celula(int x, int y, int espaçamento)
        {
            this.x = x;
            this.y = y;
            this.space = espaçamento;
            this.pos_x = (int)(x/space)*space;
            this.pos_y = (int)(y/space)*space;
        }
        public override bool Equals(object? obj)
        {
            if (obj is Celula other)
            {
                if (other.x < 0 || other.y < 0) return false;
                return pos_x == other.pos_x && pos_y == other.pos_y;
            }
            return false;
        }
        public override int GetHashCode()
        {
            return HashCode.Combine(x, y);
        }
        public static bool operator ==(Celula a, Celula b) => Equals(a, b);
        public static bool operator !=(Celula a, Celula b) => !Equals(a, b);
        public static bool operator <(Celula a, Celula b) => a.pos_x < b.pos_x || a.pos_y < b.pos_y;
        public static bool operator >(Celula a, Celula b) => a.pos_x > b.pos_x || a.pos_y > b.pos_y;
    }
}