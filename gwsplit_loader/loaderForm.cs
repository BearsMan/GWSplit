using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using GWCA.Memory;

namespace kaosbox_loader
{
    public partial class loaderForm : Form
    {
        Dictionary<string, GWCAMemory> clients;


        public loaderForm()
        {
            InitializeComponent();
        }

        private void loaderForm_Load(object sender, EventArgs e)
        {
            IntPtr pCharname = (IntPtr)0x00A2AE80;
            clients = new Dictionary<string, GWCAMemory>();

            Process[] procs = Process.GetProcessesByName("Gw");
            if(procs.Length == 0)
            {
                MessageBox.Show("No Guild Wars clients found. Please start the client before running this.");
                Application.Exit();
            }
            foreach ( Process proc in procs)
            {
                GWCAMemory mem = new GWCAMemory(proc);
                string name = mem.ReadWString(pCharname, 30);

                if (name == "") continue;

                clients.Add(name, mem);

            }
            comboBoxCharnames.DataSource        = new BindingSource(clients, null);
            comboBoxCharnames.DisplayMember     = "Key";
            comboBoxCharnames.ValueMember       = "Value";
        }

        private void buttonGo_Click(object sender, EventArgs e)
        {
            if ((GWCAMemory)comboBoxCharnames.SelectedValue != null)
                ((GWCAMemory)comboBoxCharnames.SelectedValue).LoadModule("GWSplit.dll");
            Application.Exit();
        }
    }
}
