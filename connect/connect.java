
import java.sql.*;
class connect {
	
	public static Connection conn;
	public static void main(String args[]){
		try {
			Class.forName("com.mysql.jdbc.Driver");

			System.out.println("加载成功");
				conn = DriverManager.getConnection
						("jdbc:mysql://localhost:3306", "dick", "123");
			System.out.println("连接成功");
			conn.close();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
/*	
	public static Connection getConn()
	{
		try {
			Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
			System.out.println("������ɹ�");
				conn = DriverManager.getConnection
						("jdbc:sqlserver://127.0.0.1:3306;DatabaseName=OrderDB", "dick", "123");
			System.out.println("���ӳɹ�");
			//conn.close();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return conn;
	}
/*	
	public static ResultSet update( String sql ){
		conn = data.connect.getConn();
		ResultSet ret = null;
		try {
			Statement statement = conn.createStatement();
			System.out.println(sql);
			ret = statement.executeQuery(sql);
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return ret;
	}
*/	
}
