using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Services
{
    public static class ServerData
    {
        public static Dictionary<string, string> ClientesConectados = new Dictionary<string, string>(); //Key: User, Value: URI
        public static Queue<string> MensajesPendientes = new Queue<string>();
        public static Queue<string> Desconecciones = new Queue<string>();
        public static string User;
    }
}
