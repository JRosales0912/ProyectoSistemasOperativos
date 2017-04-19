using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.IO;

namespace Services
{
    public class RemoteServices : MarshalByRefObject
    {
        private string URI;
        
        public bool Connect(string user, string URI)
        {
            if (ServerData.ClientesConectados.ContainsKey(user))
            {
                return false;
            }

            ServerData.ClientesConectados.Add(user, URI);

            return true;
        }

        public void Send(string user, string message)
        {
            lock (this)
            {
                ServerData.MensajesPendientes.Enqueue(user + ": " + message);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="path">DIrectorio del cual se desea obtener los datos</param>
        /// <returns>Si devuelve un valor null significa que el directorio no existe o es inaccesible</returns>
        public string ListDir(string path)
        {
            try
            {
                string[] archivos = Directory.GetFiles(path);
                string output = Services.ServerData.User + ": ";
                foreach (string item in archivos)
                {
                    output += item + ", ";
                }

                return output;
            }
            catch (Exception)
            {
                return ServerData.User + ": El path " + path + " no existe";
            }
        }

        public void Disconnect(string URI)
        {
            try
            {
                ServerData.Desconecciones.Enqueue(URI);
            }
            catch (Exception)
            {
            }
        }
    }
}