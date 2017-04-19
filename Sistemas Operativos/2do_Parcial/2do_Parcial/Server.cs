using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Remoting;
using System.Runtime.Remoting.Channels;
using System.Runtime.Remoting.Channels.Tcp;
using System.Windows.Forms;
using Services;

namespace _2do_Parcial
{
    public class Server
    {
        public Dictionary<string, RemoteServices> Senders;
        TcpChannel Channel;
        public string ServerUri { get; private set; }

        /// <summary>
        /// Inicialización de los servicios
        /// </summary>
        /// <param name="port">Puerto en el cual se va a montar el servidor</param>
        /// <param name="output">RichTextBox que se utiliza como consola de salida</param>
        /// <param name="user">Usuario a utilizar para las distintas conexiones</param>
        public Server(string port, RichTextBox output, string user)
        {
            try
            {
                //Port initialization
                Channel = new TcpChannel(Int32.Parse(port));
                ChannelServices.RegisterChannel(Channel, false);

                //Server initialization
                Senders = new Dictionary<string, RemoteServices>();
                RemotingConfiguration.RegisterWellKnownServiceType(typeof(RemoteServices), "Chat", WellKnownObjectMode.Singleton);
                ServerUri = ((ChannelDataStore)Channel.ChannelData).ChannelUris[0] + "/Chat";
                output.AppendText(Utilidades.MensajeExito("Listener levantado en: " + ServerUri));

                ServerData.User = user;
                Services.ServerData.User = user;
            }
            catch (Exception)
            {
                throw new Exception("No fue posible levantar el listener en el puerto: " + port);
            }
        }

        /// <summary>
        /// Conexión a un servidor específico
        /// </summary>
        /// <param name="ip">IP del servidor al que me quiero conectar</param>
        /// <param name="port">Puerto en el cual se encuentra levantado el servidor al que se va a realizar la conexión</param>
        /// <param name="output">Consola de texto para mostrar la salida</param>
        public void NewSender(string ip, string port, RichTextBox output)
        {
            string uri = "tcp://" + ip + ":" + port + "/Chat";

            if (uri == ServerUri)
            {
                throw new Exception("No se puede conectar a su propio servidor.");
            }

            //Se inicia el acceso remoto
            RemoteServices sender = (RemoteServices)Activator.GetObject(typeof(RemoteServices), uri);
            if (Senders.ContainsKey(uri))
            {
                throw new Exception("La conexión a: " + uri + " ya se encuentra activa.");
            }

            bool conexionExitosa = false;

            try
            {
                conexionExitosa = sender.Connect(ServerData.User, ServerUri);
            }
            catch (Exception)
            {
                throw new Exception("El servidor " + uri + " no se encuentra activo");
            }

            //Se verifica si se logro realizar la conexión con el servidor en cuestión
            if(!conexionExitosa)
            {
                throw new Exception("No se puede realizar la conexión a: " + uri + ", el usuario " + ServerData.User + " ya se encuentra en ese servidor");
            }

            Senders.Add(uri, sender);
            output.AppendText(Utilidades.MensajeExito("Conexión exitosa a: " + uri));
        }
        
        /// <summary>
        /// Se envía el mensaje a todos aquellos que el servidor esta conectado
        /// </summary>
        /// <param name="message">Mensaje a enviar</param>
        /// <returns></returns>
        public List<string> SendMessage(string message)
        {
            List<string> salida = new List<string>();

            foreach (KeyValuePair<string, RemoteServices> item in Senders)
            {
                try
                {
                    item.Value.Send(ServerData.User, message);
                }
                catch (Exception)
                {
                    salida.Add("\t " + item.Key);
                }
            }

            return salida;
        }

        /// <summary>
        /// Lista de carpetas de los clientes a los que esta conectado el servidor
        /// </summary>
        /// <param name="path">Directorio a buscar</param>
        /// <returns>0 = archivos, 1 = errores</returns>
        public List<string>[] ListDir(string path)
        {
            List<string> archivos = new List<string>();
            List<string> errores = new List<string>();

            foreach (KeyValuePair<string, RemoteServices> item in Senders)
            {
                try
                {
                    archivos.Add(item.Value.ListDir(path));
                }
                catch (Exception)
                {
                    errores.Add("\t " + item.Key);
                }
            }

            List<string>[] salida = { archivos, errores};
            return salida;
        }

        /// <summary>
        /// Se desconecta a un cliente que este asociado a nuestro servidor
        /// </summary>
        /// <param name="user">Usuario que se desea desconectar</param>
        public void Disconnect(string user)
        {
            if (!ServerData.ClientesConectados.ContainsKey(user))
            {
                throw new Exception("El usuario que desea eliminar no esta conectado a nuestro servidor.");
            }
            string uri = ServerData.ClientesConectados[user];

            RemoteServices client = (RemoteServices)Activator.GetObject(typeof(RemoteServices), uri);
            try
            {
                client.Disconnect(ServerUri);
                ServerData.ClientesConectados.Remove(user);
            }
            catch (Exception)
            {
                throw new Exception("El cliente que se desea desconectar no esta en línea actualmente. Pruebe más tarde.");
            }
        }
    }
}
