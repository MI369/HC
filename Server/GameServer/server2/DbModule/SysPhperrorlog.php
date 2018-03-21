<?php
require_once ($GLOBALS ['GAME_ROOT'] . "CMySQL.php");
require_once ("SQLUtil.php");
/**
 *  [The generated files]
 */

class SysPhperrorlog {
	
	private /*int*/ $id; //PRIMARY KEY 
	private /*string*/ $level;
	private /*string*/ $category;
	private /*int*/ $logtime;
	private /*string*/ $message;

	
	private $this_table_status_field = false;
	private $id_status_field = false;
	private $level_status_field = false;
	private $category_status_field = false;
	private $logtime_status_field = false;
	private $message_status_field = false;


	public static function  loadedTable( $fields=NULL,$condition=NULL)
	{
		$result = array();
		
		$p = "*";
		
		if(!empty($fields))
		{
			$p = SQLUtil::parseFields($fields);			
		}
		if (empty($condition))
		{
			$sql = "SELECT {$p} FROM `phperrorlog`";
		}
		else
		{			
			$sql = "SELECT {$p} FROM `phperrorlog` WHERE ".SQLUtil::parseCondition($condition);
		}			
		
		$qr = MySQL::getInstance()->RunQuery($sql);
		if(empty($qr)){
			return $result;
		}
		$ar = MySQL::getInstance()->FetchAllRows($qr);
		
		if (empty($ar) || count($ar) == 0)
		{
			return $result;
		}
		
		foreach($ar as $row)
		{
			$tb = new SysPhperrorlog();			
			if (isset($row['id'])) $tb->id = intval($row['id']);
			if (isset($row['level'])) $tb->level = $row['level'];
			if (isset($row['category'])) $tb->category = $row['category'];
			if (isset($row['logtime'])) $tb->logtime = intval($row['logtime']);
			if (isset($row['message'])) $tb->message = $row['message'];
		
			$result[] = $tb;
		}
		
		return $result;
	}	
	
	public static function insertSqlHeader($fields=NULL)
	{
		$result = array();				
		if(!empty($fields)){
			$where = SQLUtil::parseFields($fields);			
			$result[0] = "INSERT INTO `phperrorlog` ({$where}) VALUES ";	
			$ar = array();
			foreach($fields as $key){
				$ar[$key]=1;
			}
			$result[1] = $ar;
		}else{
			$result[0]="INSERT INTO `phperrorlog` (`id`,`level`,`category`,`logtime`,`message`) VALUES ";
			$result[1] = array('id'=>1,'level'=>1,'category'=>1,'logtime'=>1,'message'=>1);
		}				
		return $result;
	}
		
	public function  loaded( $fields=NULL,$condition=NULL)
	{

		if (empty($condition) && empty($this->id))
		{
			return false;
		}
		
		$p = "*";
		$where = "`id` = '{$this->id}'";
		
		if(!empty($fields))
		{
			$p = SQLUtil::parseFields($fields);			
		}
	    if (!empty($condition))
		{
			$where =SQLUtil::parseCondition($condition);
		}
		
		$sql = "SELECT {$p} FROM `phperrorlog` WHERE {$where}";

		MySQL::selectDefaultDb();
		$qr = MySQL::getInstance()->RunQuery($sql);
		$ar = MySQL::getInstance()->FetchArray($qr);
		
		if (!$ar || count($ar)==0)
		{
			return false;
		}
		
		if (isset($ar['id'])) $this->id = intval($ar['id']);
		if (isset($ar['level'])) $this->level = $ar['level'];
		if (isset($ar['category'])) $this->category = $ar['category'];
		if (isset($ar['logtime'])) $this->logtime = intval($ar['logtime']);
		if (isset($ar['message'])) $this->message = $ar['message'];
		
		
		$this->clean();
		
		return true;
	}
	
	
	public function  loadedCount( $fields=NULL,$condition=NULL)
	{
	
		if (empty($condition) && empty($this->id))
		{
			return false;
		}
	
		$p = "*";
		$where = "`id` = '{$this->id}'";
	
		if(!empty($fields))
		{
			$p = SQLUtil::parseFields($fields);
		}
		if (!empty($condition))
		{
			$where =SQLUtil::parseCondition($condition);
		}
	
		$sql = "SELECT {$p} FROM `phperrorlog` WHERE {$where}";
	
				MySQL::selectDefaultDb();
		$qr = MySQL::getInstance()->RunQuery($sql);
		$ar = MySQL::getInstance()->FetchArray($qr);
	
		if (!$ar || count($ar)==0)
		{
			return false;
		}
		return $ar;
	}
	
	
	
	public function loadedExistFields()
	{
		$emptyCondition = true;
    	$emptyFields = true;
    	$fields = array();
    	$condition = array();
    	
    	if (!isset($this->id)){
    		$emptyFields = false;
    		$fields[] = 'id';
    	}else{
    		$emptyCondition = false; 
    		$condition['id']=$this->id;
    	}
    	if (!isset($this->level)){
    		$emptyFields = false;
    		$fields[] = 'level';
    	}else{
    		$emptyCondition = false; 
    		$condition['level']=$this->level;
    	}
    	if (!isset($this->category)){
    		$emptyFields = false;
    		$fields[] = 'category';
    	}else{
    		$emptyCondition = false; 
    		$condition['category']=$this->category;
    	}
    	if (!isset($this->logtime)){
    		$emptyFields = false;
    		$fields[] = 'logtime';
    	}else{
    		$emptyCondition = false; 
    		$condition['logtime']=$this->logtime;
    	}
    	if (!isset($this->message)){
    		$emptyFields = false;
    		$fields[] = 'message';
    	}else{
    		$emptyCondition = false; 
    		$condition['message']=$this->message;
    	}

    	
		if ($emptyFields)
    	{
    		unset($fields);
    	}
    	
    	if ($emptyCondition)
    	{
    		unset($condition); 
    	}
    	
    	return $this->loaded($fields,$condition);    	
	}
	
	public function  inOrUp()
	{
		$sql = $this->getInSQL();
		if (empty($sql))
		{
			return false;
		}		
		$sql .= " ON DUPLICATE KEY UPDATE ";		
		$sql .= $this->getUpFields();		
		
		MySQL::selectDefaultDb();
		$qr = MySQL::getInstance()->RunQuery($sql);
		if (!$qr)
		{
			return false;
		}
				
		if (empty($this->id))
		{
			$this->id = MySQL::getInstance()->GetInsertId();
		}		
		
		$this->clean();
		
		return true;	
		
	}
	
	public function save($condition=NULL)
	{
		if (empty($condition))
		{
			$uc = "`id`='{$this->id}'";
		}
		else
		{			
			$uc = SQLUtil::parseCondition($condition);
		}
		$sql = $this->getUpSQL($uc);
		
		if(empty($sql)){
			return true;
		}
		
		MySQL::selectDefaultDb();

		$qr = MySQL::getInstance()->RunQuery($sql);
		
		$this->clean();
				
		return (boolean)$qr;
	}
	
	public static function sql_delete($condition=NULL)
	{
		if (empty($condition))
		{
			return false;
		}
		
		$sql = "DELETE FROM `phperrorlog` WHERE ".SQLUtil::parseCondition($condition);
		
		$qr = MySQL::getInstance()->RunQuery($sql);
				
		return (boolean)$qr;
	}
	
	public function  delete()
	{
		if (!isset($this->id))
		{
			return false;
		}
		
		$sql = "DELETE FROM `phperrorlog` WHERE `id`='{$this->id}'";
		
		MySQL::selectDefaultDb();
		$qr = MySQL::getInstance()->RunQuery($sql);
				
		return (boolean)$qr;
	}
	
	public function getInsertValue($fields)
	{
		$values = "(";		
		foreach($fields as $f => $k){
			if($f == 'id'){
 				$values .= "'{$this->id}',";
 			}else if($f == 'level'){
 				$values .= "'{$this->level}',";
 			}else if($f == 'category'){
 				$values .= "'{$this->category}',";
 			}else if($f == 'logtime'){
 				$values .= "'{$this->logtime}',";
 			}else if($f == 'message'){
 				$values .= "'{$this->message}',";
 			}		
		}
		$values .= ")";
		
		return str_replace(",)",")",$values);		
	}
	
	private function  getInSQL()
	{
		if (!$this->this_table_status_field)
		{
			return;
		}		
		
		$fields = "(";
		$values = " VALUES(";

		if (isset($this->id))
		{
			$fields .= "`id`,";
			$values .= "'{$this->id}',";
		}
		if (isset($this->level))
		{
			$fields .= "`level`,";
			$values .= "'{$this->level}',";
		}
		if (isset($this->category))
		{
			$fields .= "`category`,";
			$values .= "'{$this->category}',";
		}
		if (isset($this->logtime))
		{
			$fields .= "`logtime`,";
			$values .= "'{$this->logtime}',";
		}
		if (isset($this->message))
		{
			$fields .= "`message`,";
			$values .= "'{$this->message}',";
		}

		
		$fields .= ")";
		$values .= ")";
		
		$sql = "INSERT INTO `phperrorlog` ".$fields.$values;
		
		return str_replace(",)",")",$sql);
	}
	
	private function  getUpFields()
	{
		$update = "";
		
		if ($this->level_status_field)
		{			
			if (!isset($this->level))
			{
				$update .= ("`level`=null,");
			}
			else
			{
				$update .= ("`level`='{$this->level}',");
			}
		}
		if ($this->category_status_field)
		{			
			if (!isset($this->category))
			{
				$update .= ("`category`=null,");
			}
			else
			{
				$update .= ("`category`='{$this->category}',");
			}
		}
		if ($this->logtime_status_field)
		{			
			if (!isset($this->logtime))
			{
				$update .= ("`logtime`=null,");
			}
			else
			{
				$update .= ("`logtime`='{$this->logtime}',");
			}
		}
		if ($this->message_status_field)
		{			
			if (!isset($this->message))
			{
				$update .= ("`message`=null,");
			}
			else
			{
				$update .= ("`message`='{$this->message}',");
			}
		}

			
		if (empty($update) || strlen($update) < 1)
		{
			return;
		}
		
		$i = strrpos($update,",");
		if (!is_bool($i))
		{
			$update = substr($update,0,$i);
		}		
		
		return $update;
	}
	
	private function  getUpSQL($condition)
	{
		if (!$this->this_table_status_field)
		{
			return null;
		}
		
		$update = $this->getUpFields();
		
		if (empty($update))
		{
			return;
		}
		
		$sql = "UPDATE `phperrorlog` SET {$update} WHERE {$condition}";
		
		return $sql;
	}
	
	public function  add($fieldsValue,$condition=NULL)
	{				
		if (empty($condition))
		{
			$uc = "`id`='{$this->id}'";
		}
		else
		{			
			$uc = SQLUtil::parseCondition($condition);
		}
		
		$update = SQLUtil::parseASFieldValues($fieldsValue);
		
		$sql = "UPDATE `phperrorlog` SET {$update} WHERE {$uc}";
		
		MySQL::selectDefaultDb();
		$qr = MySQL::getInstance()->RunQuery($sql);
				
		return (boolean)$qr;
	}	
	
	public function sub($fieldsVal,$condition=NULL)
	{
		if (empty($condition))
		{
			$uc = "`id`='{$this->id}'";
		}
		else
		{			
			$uc = SQLUtil::parseCondition($condition);
		}
		
		$update = SQLUtil::parseASFieldValues($fieldsVal,false);
		
		$sql = "UPDATE `phperrorlog` SET {$update} WHERE {$uc}";
		
		MySQL::selectDefaultDb();
		$qr = MySQL::getInstance()->RunQuery($sql);
				
		return (boolean)$qr;
	}
	
	private function /*void*/ clean() 
	{
		$this->this_table_status_field = false;
		$this->id_status_field = false;
		$this->level_status_field = false;
		$this->category_status_field = false;
		$this->logtime_status_field = false;
		$this->message_status_field = false;

	}
	
	public function /*int*/ getId()
	{
		return $this->id;
	}
	
	public function /*void*/ setId(/*int*/ $id)
	{
		$this->id = intval($id);
		$this->id_status_field = true;		
		$this->this_table_status_field = true;		
	}

	public function /*void*/ setIdNull()
	{
		$this->id = null;
		$this->id_status_field = true;		
		$this->this_table_status_field = true;
	}

	public function /*string*/ getLevel()
	{
		return $this->level;
	}
	
	public function /*void*/ setLevel(/*string*/ $level)
	{
		$this->level = SQLUtil::toSafeSQLString($level);
		$this->level_status_field = true;		
		$this->this_table_status_field = true;		
	}

	public function /*void*/ setLevelNull()
	{
		$this->level = null;
		$this->level_status_field = true;		
		$this->this_table_status_field = true;
	}

	public function /*string*/ getCategory()
	{
		return $this->category;
	}
	
	public function /*void*/ setCategory(/*string*/ $category)
	{
		$this->category = SQLUtil::toSafeSQLString($category);
		$this->category_status_field = true;		
		$this->this_table_status_field = true;		
	}

	public function /*void*/ setCategoryNull()
	{
		$this->category = null;
		$this->category_status_field = true;		
		$this->this_table_status_field = true;
	}

	public function /*int*/ getLogtime()
	{
		return $this->logtime;
	}
	
	public function /*void*/ setLogtime(/*int*/ $logtime)
	{
		$this->logtime = intval($logtime);
		$this->logtime_status_field = true;		
		$this->this_table_status_field = true;		
	}

	public function /*void*/ setLogtimeNull()
	{
		$this->logtime = null;
		$this->logtime_status_field = true;		
		$this->this_table_status_field = true;
	}

	public function /*string*/ getMessage()
	{
		return $this->message;
	}
	
	public function /*void*/ setMessage(/*string*/ $message)
	{
		$this->message = SQLUtil::toSafeSQLString($message);
		$this->message_status_field = true;		
		$this->this_table_status_field = true;		
	}

	public function /*void*/ setMessageNull()
	{
		$this->message = null;
		$this->message_status_field = true;		
		$this->this_table_status_field = true;
	}

	
	public function /*string*/ toDebugString()
	{
		$dbg = "(";
		
		$dbg .= ("id={$this->id},");
		$dbg .= ("level={$this->level},");
		$dbg .= ("category={$this->category},");
		$dbg .= ("logtime={$this->logtime},");
		$dbg .= ("message={$this->message},");

		$dbg .= ")";
				
		return str_replace(",)",")",$dbg);
	}
}

?>
