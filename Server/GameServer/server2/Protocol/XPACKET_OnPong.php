<?php
/**
	Auto generated by xproto.exe
@author
	Dany
*/
require_once("XByteArray.php");


	class XPACKET_OnPong
	{
		    public static  $_m_xcmd/*:int*/=_EMSG_ServerEvent::SMSG_OnPong;

	    
		public $time/*:string utf-8*/="";

	    
	    public function XPACKET_OnPong()
		{
	
		}
			
		public static function _Size($time/*:string utf-8*/ )
		{
			$__xv	= 0;
			$i		=0;

            $__xv +=4;//LENGHT
            $__xv +=4;//_m_xcmd
            $__xv +=XByteArray::StringASize($time);

			return $__xv;
		}
				
		public static function _ToBuffer($__dst/*XByteArray*/,$time/*:string utf-8*/ )
		{
			$__xv	= 0;
			$i		=0;

			$__dst->writeInt32(XPACKET_OnPong::_Size($time/*:string utf-8*/ ));
			$__xv +=4;
			$__dst->writeInt32(XPACKET_OnPong::$_m_xcmd);
			$__xv +=4;

            //Write codes of time
            //
             $__xv += XByteArray::WriteStringA($__dst, $time);

			return $__xv;
		}
		
		public static function _ClassFromParameters($time/*:string utf-8*/ )
		{
			$_class = new XPACKET_OnPong();

            $_class->time=$time;
			
			return $_class;
		}


		public function FromBuffer($__src/*:XByteArray*/)
		{
			$__xv					= 0;
			$i						=0;
			$__xvBeanSize	=0;


            //Read codes of __xvtemp1
            //
            if($__src->getBytesAvailable()>=4)
            {
                $this->__xvtemp1=$__src->readInt32();
                $__xv +=4;
            }
            else
            {
                return 0;
            }

            //Read codes of __xvtemp2
            //
            if($__src->getBytesAvailable()>=4)
            {
                $this->__xvtemp2=$__src->readInt32();
                $__xv +=4;
            }
            else
            {
                return 0;
            }

            //Read codes of time
            //
            $__time_szSize	= new XInteger();
            $this->time =XByteArray::ReadStringA($__src,$__time_szSize);
            if($__time_szSize->_value<=0) 
                return 0;
            $__xv +=$__time_szSize->_value;

			return $__xv;
		}
		
		public function ToBuffer($__dst/*XByteArray*/)
		{
			return XPACKET_OnPong::_ToBuffer($__dst,$this->time );
		}
		
		public function Size()
		{
			return XPACKET_OnPong::_Size($this->time );
		}

    public  function FromXml(/*XP_XMLNODE_PTR*/ $pNode)
    {

        $this->time = XFROM_XML($this->time,$pNode,"time",2,"");

		  	return 0;
    }
    
    public  function   ToXml(/*XSTRING_STREAM & out*/)
    {
        $__xv_out="";

        $__xv_out .= XTO_XML($this->time,"time",2, 0);

        return $__xv_out;
    }
    
    public   function fromAMFObject($pNode)
    {
       
        
        $this->time = XFROM_AMFOBJECT($this->time,$pNode,"time",2,"");

        return 0;
    }
		
	private static function ParamDebugString($param)
    {
    	if (is_object($param))
    	{
    		return $param->ToDebugString();
    	}
    	else if (is_array($param))
    	{
    		$str = "(";
    		foreach($param as $p)
    		{
    			if( is_object($p) )
    			{
    				$str .= $p->ToDebugString().",";
			}
			else
			{
				$str .= strval($p).",";
			}
    		}
    		$str .= ")";
    		$str = str_replace(",)",")",$str);
    		return $str;
    	}
    	
    	return strval($param);
    } 
    
	public  function ToDebugString()
    {
    	if(XPACKET_OnPong::$_m_xcmd == _EMSG_ServerEvent::SMSG_OnSendZipData){
    		return "([ignore zip data])";
    	}
		
    	$__xv_out  = "(";
    	
        $__xv_out .= "time=".$this->ParamDebugString($this->time).",";

    	
    	$__xv_out  .= ")";
    	
    	$__xv_out = str_replace(",)",")",$__xv_out);
    	
    	return $__xv_out;
    }
    
   	public static function toAMFObject($__dst/*XByteArray*/,$time/*:string utf-8*/ )
		{
			$__xv	= 0;
			$i		=0;
      $obj = array();

        $obj["time"]=$time ;

      if(count($obj)>0)
      {
          $outBuffer  = WriteAMF3Object($obj);
          $__xv = strlen($outBuffer);
          $__xv+=8;
          $__dst->writeInt32($__xv);
          $__dst->writeInt32(XPACKET_OnPong::$_m_xcmd);
          $__dst->writeBinary($outBuffer,strlen($outBuffer));
      }
      else
      {
          $__xv =8;
          $__dst->writeInt32($__xv);
          $__dst->writeInt32(XPACKET_OnPong::$_m_xcmd);
      }
      
      
			return $__xv;
		}
	}
	
	
?>
