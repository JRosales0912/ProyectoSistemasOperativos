namespace _2do_Parcial
{
    partial class Chat
    {
        /// <summary>
        /// Variable del diseñador necesaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén usando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido de este método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Chat));
            this.txtUsuario = new System.Windows.Forms.TextBox();
            this.lbUsuario = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.txtIP = new System.Windows.Forms.TextBox();
            this.lbIP = new System.Windows.Forms.Label();
            this.txtMensaje = new System.Windows.Forms.TextBox();
            this.rchChat = new System.Windows.Forms.RichTextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.btnServer = new System.Windows.Forms.Button();
            this.pServer = new System.Windows.Forms.Panel();
            this.mskPuertoServer = new System.Windows.Forms.MaskedTextBox();
            this.rchSalida = new System.Windows.Forms.RichTextBox();
            this.mskPuertoConnect = new System.Windows.Forms.MaskedTextBox();
            this.pChat = new System.Windows.Forms.Panel();
            this.lbServerUser = new System.Windows.Forms.Label();
            this.pbDisconnect = new System.Windows.Forms.PictureBox();
            this.pbSenders = new System.Windows.Forms.PictureBox();
            this.pbClients = new System.Windows.Forms.PictureBox();
            this.pbConnect = new System.Windows.Forms.PictureBox();
            this.pbList = new System.Windows.Forms.PictureBox();
            this.pbSend = new System.Windows.Forms.PictureBox();
            this.pServer.SuspendLayout();
            this.pChat.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbDisconnect)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbSenders)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbClients)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbConnect)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbList)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbSend)).BeginInit();
            this.SuspendLayout();
            // 
            // txtUsuario
            // 
            this.txtUsuario.Location = new System.Drawing.Point(255, 178);
            this.txtUsuario.Name = "txtUsuario";
            this.txtUsuario.Size = new System.Drawing.Size(139, 22);
            this.txtUsuario.TabIndex = 1;
            // 
            // lbUsuario
            // 
            this.lbUsuario.AutoSize = true;
            this.lbUsuario.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbUsuario.ForeColor = System.Drawing.Color.Black;
            this.lbUsuario.Location = new System.Drawing.Point(175, 181);
            this.lbUsuario.Name = "lbUsuario";
            this.lbUsuario.Size = new System.Drawing.Size(74, 17);
            this.lbUsuario.TabIndex = 26;
            this.lbUsuario.Text = "Usuario :";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Black;
            this.label1.Location = new System.Drawing.Point(299, 64);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(61, 17);
            this.label1.TabIndex = 21;
            this.label1.Text = "Puerto:";
            // 
            // txtIP
            // 
            this.txtIP.Enabled = false;
            this.txtIP.Location = new System.Drawing.Point(366, 35);
            this.txtIP.Name = "txtIP";
            this.txtIP.Size = new System.Drawing.Size(105, 22);
            this.txtIP.TabIndex = 4;
            // 
            // lbIP
            // 
            this.lbIP.AutoSize = true;
            this.lbIP.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbIP.ForeColor = System.Drawing.Color.Black;
            this.lbIP.Location = new System.Drawing.Point(333, 38);
            this.lbIP.Name = "lbIP";
            this.lbIP.Size = new System.Drawing.Size(27, 17);
            this.lbIP.TabIndex = 19;
            this.lbIP.Text = "IP:";
            // 
            // txtMensaje
            // 
            this.txtMensaje.Enabled = false;
            this.txtMensaje.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtMensaje.Location = new System.Drawing.Point(18, 470);
            this.txtMensaje.Name = "txtMensaje";
            this.txtMensaje.Size = new System.Drawing.Size(422, 23);
            this.txtMensaje.TabIndex = 18;
            // 
            // rchChat
            // 
            this.rchChat.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rchChat.Location = new System.Drawing.Point(18, 134);
            this.rchChat.Name = "rchChat";
            this.rchChat.ReadOnly = true;
            this.rchChat.Size = new System.Drawing.Size(515, 329);
            this.rchChat.TabIndex = 17;
            this.rchChat.Text = "";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.Black;
            this.label2.Location = new System.Drawing.Point(188, 211);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(61, 17);
            this.label2.TabIndex = 28;
            this.label2.Text = "Puerto:";
            // 
            // btnServer
            // 
            this.btnServer.BackColor = System.Drawing.Color.DarkSlateGray;
            this.btnServer.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnServer.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnServer.ForeColor = System.Drawing.Color.White;
            this.btnServer.Location = new System.Drawing.Point(235, 236);
            this.btnServer.Name = "btnServer";
            this.btnServer.Size = new System.Drawing.Size(103, 25);
            this.btnServer.TabIndex = 3;
            this.btnServer.Text = "Iniciar";
            this.btnServer.UseVisualStyleBackColor = false;
            this.btnServer.Click += new System.EventHandler(this.btnServer_Click);
            // 
            // pServer
            // 
            this.pServer.Controls.Add(this.mskPuertoServer);
            this.pServer.Controls.Add(this.btnServer);
            this.pServer.Controls.Add(this.lbUsuario);
            this.pServer.Controls.Add(this.txtUsuario);
            this.pServer.Controls.Add(this.label2);
            this.pServer.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.pServer.Location = new System.Drawing.Point(579, 12);
            this.pServer.Name = "pServer";
            this.pServer.Size = new System.Drawing.Size(545, 497);
            this.pServer.TabIndex = 31;
            // 
            // mskPuertoServer
            // 
            this.mskPuertoServer.Location = new System.Drawing.Point(255, 208);
            this.mskPuertoServer.Mask = "99999";
            this.mskPuertoServer.Name = "mskPuertoServer";
            this.mskPuertoServer.Size = new System.Drawing.Size(139, 22);
            this.mskPuertoServer.TabIndex = 2;
            this.mskPuertoServer.ValidatingType = typeof(int);
            // 
            // rchSalida
            // 
            this.rchSalida.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rchSalida.Location = new System.Drawing.Point(12, 515);
            this.rchSalida.Name = "rchSalida";
            this.rchSalida.ReadOnly = true;
            this.rchSalida.Size = new System.Drawing.Size(545, 70);
            this.rchSalida.TabIndex = 32;
            this.rchSalida.Text = "";
            // 
            // mskPuertoConnect
            // 
            this.mskPuertoConnect.Enabled = false;
            this.mskPuertoConnect.Location = new System.Drawing.Point(366, 61);
            this.mskPuertoConnect.Mask = "99999";
            this.mskPuertoConnect.Name = "mskPuertoConnect";
            this.mskPuertoConnect.Size = new System.Drawing.Size(105, 22);
            this.mskPuertoConnect.TabIndex = 5;
            this.mskPuertoConnect.ValidatingType = typeof(int);
            // 
            // pChat
            // 
            this.pChat.Controls.Add(this.lbServerUser);
            this.pChat.Controls.Add(this.pbDisconnect);
            this.pChat.Controls.Add(this.pbSenders);
            this.pChat.Controls.Add(this.pbClients);
            this.pChat.Controls.Add(this.pbConnect);
            this.pChat.Controls.Add(this.pbList);
            this.pChat.Controls.Add(this.pbSend);
            this.pChat.Controls.Add(this.rchChat);
            this.pChat.Controls.Add(this.mskPuertoConnect);
            this.pChat.Controls.Add(this.label1);
            this.pChat.Controls.Add(this.txtMensaje);
            this.pChat.Controls.Add(this.txtIP);
            this.pChat.Controls.Add(this.lbIP);
            this.pChat.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.pChat.Location = new System.Drawing.Point(12, 12);
            this.pChat.Name = "pChat";
            this.pChat.Size = new System.Drawing.Size(545, 497);
            this.pChat.TabIndex = 36;
            this.pChat.Visible = false;
            // 
            // lbServerUser
            // 
            this.lbServerUser.AutoSize = true;
            this.lbServerUser.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbServerUser.ForeColor = System.Drawing.Color.Black;
            this.lbServerUser.Location = new System.Drawing.Point(255, 104);
            this.lbServerUser.Name = "lbServerUser";
            this.lbServerUser.Size = new System.Drawing.Size(86, 16);
            this.lbServerUser.TabIndex = 42;
            this.lbServerUser.Text = "Server User: ";
            // 
            // pbDisconnect
            // 
            this.pbDisconnect.Cursor = System.Windows.Forms.Cursors.Hand;
            this.pbDisconnect.Enabled = false;
            this.pbDisconnect.Image = ((System.Drawing.Image)(resources.GetObject("pbDisconnect.Image")));
            this.pbDisconnect.Location = new System.Drawing.Point(508, 469);
            this.pbDisconnect.Name = "pbDisconnect";
            this.pbDisconnect.Size = new System.Drawing.Size(25, 23);
            this.pbDisconnect.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pbDisconnect.TabIndex = 41;
            this.pbDisconnect.TabStop = false;
            this.pbDisconnect.Click += new System.EventHandler(this.pbDisconnect_Click);
            // 
            // pbSenders
            // 
            this.pbSenders.Image = ((System.Drawing.Image)(resources.GetObject("pbSenders.Image")));
            this.pbSenders.Location = new System.Drawing.Point(139, 10);
            this.pbSenders.Name = "pbSenders";
            this.pbSenders.Size = new System.Drawing.Size(110, 110);
            this.pbSenders.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pbSenders.TabIndex = 40;
            this.pbSenders.TabStop = false;
            this.pbSenders.Click += new System.EventHandler(this.pbSenders_Click);
            // 
            // pbClients
            // 
            this.pbClients.Image = ((System.Drawing.Image)(resources.GetObject("pbClients.Image")));
            this.pbClients.Location = new System.Drawing.Point(18, 10);
            this.pbClients.Name = "pbClients";
            this.pbClients.Size = new System.Drawing.Size(110, 110);
            this.pbClients.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pbClients.TabIndex = 39;
            this.pbClients.TabStop = false;
            this.pbClients.Click += new System.EventHandler(this.pbClients_Click);
            // 
            // pbConnect
            // 
            this.pbConnect.Cursor = System.Windows.Forms.Cursors.Hand;
            this.pbConnect.Enabled = false;
            this.pbConnect.Image = ((System.Drawing.Image)(resources.GetObject("pbConnect.Image")));
            this.pbConnect.Location = new System.Drawing.Point(477, 53);
            this.pbConnect.Name = "pbConnect";
            this.pbConnect.Size = new System.Drawing.Size(30, 30);
            this.pbConnect.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pbConnect.TabIndex = 38;
            this.pbConnect.TabStop = false;
            this.pbConnect.Click += new System.EventHandler(this.pbConnect_Click);
            // 
            // pbList
            // 
            this.pbList.Cursor = System.Windows.Forms.Cursors.Hand;
            this.pbList.Enabled = false;
            this.pbList.Image = ((System.Drawing.Image)(resources.GetObject("pbList.Image")));
            this.pbList.Location = new System.Drawing.Point(477, 469);
            this.pbList.Name = "pbList";
            this.pbList.Size = new System.Drawing.Size(25, 23);
            this.pbList.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pbList.TabIndex = 37;
            this.pbList.TabStop = false;
            this.pbList.Click += new System.EventHandler(this.pbList_Click);
            // 
            // pbSend
            // 
            this.pbSend.Cursor = System.Windows.Forms.Cursors.Hand;
            this.pbSend.Enabled = false;
            this.pbSend.Image = ((System.Drawing.Image)(resources.GetObject("pbSend.Image")));
            this.pbSend.Location = new System.Drawing.Point(446, 469);
            this.pbSend.Name = "pbSend";
            this.pbSend.Size = new System.Drawing.Size(25, 23);
            this.pbSend.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pbSend.TabIndex = 37;
            this.pbSend.TabStop = false;
            this.pbSend.Click += new System.EventHandler(this.pbSend_Click);
            // 
            // Chat
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(567, 596);
            this.Controls.Add(this.pChat);
            this.Controls.Add(this.rchSalida);
            this.Controls.Add(this.pServer);
            this.Name = "Chat";
            this.Text = "Chat";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Chat_FormClosing);
            this.Load += new System.EventHandler(this.Chat_Load);
            this.pServer.ResumeLayout(false);
            this.pServer.PerformLayout();
            this.pChat.ResumeLayout(false);
            this.pChat.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbDisconnect)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbSenders)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbClients)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbConnect)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbList)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbSend)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TextBox txtUsuario;
        private System.Windows.Forms.Label lbUsuario;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtIP;
        private System.Windows.Forms.Label lbIP;
        private System.Windows.Forms.TextBox txtMensaje;
        private System.Windows.Forms.RichTextBox rchChat;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btnServer;
        private System.Windows.Forms.Panel pServer;
        private System.Windows.Forms.RichTextBox rchSalida;
        private System.Windows.Forms.MaskedTextBox mskPuertoServer;
        private System.Windows.Forms.MaskedTextBox mskPuertoConnect;
        private System.Windows.Forms.Panel pChat;
        private System.Windows.Forms.PictureBox pbSend;
        private System.Windows.Forms.PictureBox pbList;
        private System.Windows.Forms.PictureBox pbConnect;
        private System.Windows.Forms.PictureBox pbSenders;
        private System.Windows.Forms.PictureBox pbClients;
        private System.Windows.Forms.PictureBox pbDisconnect;
        private System.Windows.Forms.Label lbServerUser;
    }
}

