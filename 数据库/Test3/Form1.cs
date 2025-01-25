using MySql.Data.MySqlClient;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Test3
{
    public partial class Form1 : Form
    {
        string connetStr ="server=localhost;port=3306;user = root;password=123456;database=test";
        MySqlConnection myconnection;
        public Form1()
        {
            InitializeComponent();
            Form1_Load(null, null);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            label1.ForeColor = Color.Green;
            label1.Text = "操作状态";

            label2.Text = "姓名";
            label3.Text = "邮箱";
            label4.Text = "电话";
            label5.Text = "性别";

            textBox1.Name = "tB_Name";
            textBox2.Name = "tB_Mail";
            textBox3.Name = "tB_Phone";
            comboBox1.Name = "cB_Sex";
            comboBox1.Items.Add("男");
            comboBox1.Items.Add("女");

            label6.Text = "查询条件";
            comboBox2.Name = "cB_tj";
            comboBox2.Items.Add("全部");
            comboBox2.Items.Add("姓名");
            comboBox2.Items.Add("邮箱");
            comboBox2.Items.Add("电话");
            comboBox2.Items.Add("性别");
            checkBox1.Name = "chk_mode";
            checkBox1.Text = "模糊查询";

            button1.Text = "连接";
            button1.Name = "btConnect";
            button2.Text = "查询";
            button2.Name = "btQueryAll";
            button3.Text = "插入";
            button3.Name = "btInsertToDatabase";
            button4.Text = "修改";
            button4.Name = "btModifiFeildValue";
            button5.Text = "删除";
            button5.Name = "btDeleteFeildValue";
            button6.Text = "断开连接";
            button6.Name = "btDisConnect";
        }
        //连接按钮
        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                myconnection = new MySqlConnection(connetStr);
                myconnection.Open();
                label1.Text = "数据库连接成功";
            }
            catch (MySqlException ex)
            {
                MessageBox.Show("数据库连接失败" + ex.ToString());
            }
        }

        public string DisConnect()
        {
            try
            {
                myconnection.Close();
                return "数据库断开成功";
            }
            catch (MySqlException ex)
            {
                return "数据库断开失败" + ex.ToString();
            }
        }   
        //断开连接按钮
        private void button6_Click(object sender, EventArgs e)
        {
            label1.Text = DisConnect();
        }

        //插入按钮
        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                string strSQL1,strname,strmail,strphone,strsex;
                strname = textBox1.Text;
                strmail = textBox2.Text;
                strphone = textBox3.Text;
                strsex = comboBox1.Text;
                strSQL1 = String.Format("insert into TXL values('{0}','{1}','{2}','{3}')", strname, strmail, strphone, strsex);

                MySqlDataAdapter objDataAdpter = new MySqlDataAdapter();
                MySqlCommand thisCommand = new MySqlCommand(strSQL1, myconnection);
                thisCommand.ExecuteNonQuery();

                string strSQL2 = "select * from TXL";
                MySqlDataAdapter objDataAdpter1 = new MySqlDataAdapter();
                objDataAdpter1.SelectCommand = new MySqlCommand(strSQL2, myconnection);
                DataSet ds = new DataSet();
                objDataAdpter1.Fill(ds);
                dataGridView1.DataSource = ds.Tables[0];
            }
            catch (Exception ex)
            {
                MessageBox.Show("插入失败" + ex.ToString());
            }
        }
        //查询按钮
        private void button2_Click(object sender, EventArgs e)
        {
            string strSQL = "";
            try
            {        
                switch(comboBox2.Text)
                {
                    case "全部":
                        strSQL = "select * from TXL";
                        break;
                    case "姓名":
                        if (checkBox1.Checked)
                            strSQL = String.Format("select * from TXL where name like '%{0}%'", textBox1.Text);
                        else
                            strSQL = String.Format("select * from TXL where name = '{0}'", textBox1.Text);
                        break;
                    case "邮箱":
                        if (checkBox1.Checked)
                            strSQL = String.Format("select * from TXL where mail like '%{0}%'", textBox2.Text);
                        else
                            strSQL = String.Format("select * from TXL where mail = '{0}'", textBox2.Text);
                        break;
                    case "电话":
                        if (checkBox1.Checked)
                            strSQL = String.Format("select * from TXL where phone like '%{0}%'", textBox3.Text);
                        else
                            strSQL = String.Format("select * from TXL where phone = '{0}'", textBox3.Text);
                        break;
                    case "性别":
                        if (checkBox1.Checked)
                            strSQL = String.Format("select * from TXL where sex like '%{0}%'", comboBox1.Text);
                        else
                            strSQL = String.Format("select * from TXL where sex = '{0}'", comboBox1.Text);
                        break;
                }
                MySqlCommand cmd =new MySqlCommand(strSQL, myconnection);
                MySqlDataAdapter adpt1 = new MySqlDataAdapter(cmd);

                DataSet ds = new DataSet();
                adpt1.Fill(ds);
                dataGridView1.DataSource = ds.Tables[0];
            }
            catch (Exception ex)
            {
                MessageBox.Show("查询失败" + ex.ToString());
            }
        }
        //修改按钮
        private void button4_Click(object sender, EventArgs e)
        {
            try
            {
                string strSQL1 = string.Format("update TXL set mail='{0}',phone='{1}',sex='{2}' where name='{3}'", textBox2.Text, textBox3.Text, comboBox1.Text, textBox1.Text);
                MySqlCommand thisCommand = new MySqlCommand(strSQL1, myconnection);
                thisCommand.ExecuteNonQuery();

                string strSQL2 = "select * from TXL";
                MySqlDataAdapter objDataAdpter1 = new MySqlDataAdapter();
                objDataAdpter1.SelectCommand = new MySqlCommand(strSQL2, myconnection);
                DataSet ds = new DataSet();
                objDataAdpter1.Fill(ds, "TXL");
                dataGridView1.DataSource = ds.Tables[0];
            }
            catch (Exception ex)
            {
                MessageBox.Show("修改失败" + ex.ToString());
            }
        }
        //删除按钮
        private void button5_Click(object sender, EventArgs e)
        {
            try
            {
                string strSQL1 = string.Format("delete from TXL where name='{0}'", textBox1.Text);
                MySqlCommand thisCommand = new MySqlCommand(strSQL1, myconnection);
                thisCommand.ExecuteNonQuery();

                string strSQL2 = "select * from TXL";
                MySqlDataAdapter objDataAdpter1 = new MySqlDataAdapter();
                objDataAdpter1.SelectCommand = new MySqlCommand(strSQL2, myconnection);
                DataSet ds = new DataSet();
                objDataAdpter1.Fill(ds, "TXL");
                dataGridView1.DataSource = ds.Tables[0];
            }
            catch (Exception ex)
            {
                MessageBox.Show("删除失败" + ex.ToString());
            }
        }
    }
}
