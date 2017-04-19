using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _2do_Parcial
{
    public static class Utilidades
    {
        public static string MensajeExito(string mensaje)
        {
            return "-" + mensaje + "-\n";
        }

        public static string MensajeError(string mensaje)
        {
            return "-Error: " + mensaje + "-\n";
        }

        public static string MensajeError(Exception mensaje)
        {
            return "-Error: " + mensaje.Message + "-\n";
        }
    }
}
