using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using Services;

namespace _2do_Parcial
{
    public partial class Chat : Form
    {
        private Server Listener;
        Thread Mensajes;
        Thread Desconectados;

        public Chat()
        {
            InitializeComponent();
        }

        private void RevisarEntrada(string entrada, string nombreEntrada)
        {
            if (entrada.Trim().Equals(""))
            {
                throw new Exception("Debe de ingresar un(a) " + nombreEntrada + " válido(a)");
            }
        }

        private void RevisionMensajes()
        {
            while (true)
            {
                Thread.Sleep(10);
                lock(this)
                {
                    if (ServerData.MensajesPendientes.Count != 0)
                    {
                        rchChat.AppendText(ServerData.MensajesPendientes.Dequeue() + "\n");
                    }
                }
            }
        }

        private void RevisionDesconexiones()
        {
            while (true)
            {
                Thread.Sleep(10);
                lock (this)
                {
                    if (ServerData.Desconecciones.Count != 0)
                    {
                        string uri = ServerData.Desconecciones.Dequeue();
                        Listener.Senders.Remove(uri);
                        rchChat.AppendText("-- El servidor " + uri + " no recibira más tus mensajes --" + "\n");
                    }
                }
            }
        }

        private void Chat_Load(object sender, EventArgs e)
        {
            pServer.Location = new Point(12,12);
            Mensajes = new Thread(RevisionMensajes);
            Mensajes.Start();
            Desconectados = new Thread(RevisionDesconexiones);
            Desconectados.Start();
        }

        /// <summary>
        /// Se levantan los servicios del servidor
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnServer_Click(object sender, EventArgs e)
        {
            try
            {
                RevisarEntrada(mskPuertoServer.Text, "puerto");
                RevisarEntrada(txtUsuario.Text, "usuario");

                Listener = new Server(mskPuertoServer.Text.Trim(), rchSalida, txtUsuario.Text);
                Services.ServerData.User = txtUsuario.Text.Trim();

                pbSend.Enabled = true;
                pbList.Enabled = true;
                pbConnect.Enabled = true;
                pbDisconnect.Enabled = true;
                txtMensaje.Enabled = true;
                txtIP.Enabled = true;
                mskPuertoConnect.Enabled = true;
                pChat.Visible = true;

                lbServerUser.Text += Services.ServerData.User;
            }
            catch (Exception ex)
            {
                rchSalida.AppendText(Utilidades.MensajeError(ex));
            }
        }

        private void Chat_FormClosing(object sender, FormClosingEventArgs e)
        {
            Mensajes.Abort();
            Desconectados.Abort();
        }

        private void pbList_Click(object sender, EventArgs e)
        {
            try
            {
                RevisarEntrada(txtMensaje.Text, "directorio");
                List<string>[] archivos = Listener.ListDir(txtMensaje.Text.Trim());

                foreach (string item in archivos[0])
                {
                    rchChat.AppendText(item + "\n");
                }

                foreach (string item in archivos[1])
                {
                    rchSalida.AppendText(Utilidades.MensajeError(item));
                }
            }
            catch (Exception ex)
            {
                rchSalida.AppendText(Utilidades.MensajeError(ex));
            }

            txtMensaje.Text = "";
        }

        private void pbSend_Click(object sender, EventArgs e)
        {
            try
            {
                RevisarEntrada(txtMensaje.Text, "mensaje");
                rchChat.AppendText(ServerData.User + ": " + txtMensaje.Text + "\n");
                List<string> salida = Listener.SendMessage(txtMensaje.Text.Trim());

                if (salida.Count != 0)
                {
                    string output = "El mensaje no se envio a los siguientes servidores: \n";
                    foreach (string item in salida)
                    {
                        output += item;
                    }

                    throw new Exception(output);
                }
                else
                {
                    rchSalida.AppendText(Utilidades.MensajeExito("Mensajes enviados correctamente"));
                }
            }
            catch (Exception ex)
            {
                rchSalida.AppendText(Utilidades.MensajeError(ex));
            }

            txtMensaje.Text = "";
        }

        private void pbConnect_Click(object sender, EventArgs e)
        {
            try
            {
                RevisarEntrada(mskPuertoConnect.Text, "puerto");
                RevisarEntrada(txtIP.Text, "IP");

                Listener.NewSender(txtIP.Text.Trim(), mskPuertoConnect.Text.Trim(), rchChat);
                txtIP.Text = "";
                mskPuertoConnect.Text = "";
            }
            catch (Exception ex)
            {
                rchSalida.AppendText(Utilidades.MensajeError(ex));
            }
        }

        private void pbDisconnect_Click(object sender, EventArgs e)
        {
            try
            {
                RevisarEntrada(txtMensaje.Text, "mensaje");
                Listener.Disconnect(txtMensaje.Text);
                rchChat.AppendText("-- El usuario " + txtMensaje.Text + " se desconecto correctamente --'\n");
            }
            catch (Exception ex)
            {
                rchSalida.AppendText(Utilidades.MensajeError(ex));
            }

            txtMensaje.Text = "";
        }

        private void pbClients_Click(object sender, EventArgs e)
        {
            string salida = "-- Clientes: \n";
            foreach (KeyValuePair<string, string> item in ServerData.ClientesConectados)
            {
                salida += "\t*" + item.Key + " " + item.Value + "\n";
            }

            lock (this)
            {
                rchChat.AppendText(salida);
            }
        }

        private void pbSenders_Click(object sender, EventArgs e)
        {
            string salida = "-- Senders: \n";
            foreach (string item in Listener.Senders.Keys)
            {
                salida += "\t*" + item + "\n";
            }

            lock (this)
            {
                rchChat.AppendText(salida);
            }
        }
    }
}
