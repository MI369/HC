<?php
/**
	Auto generated by xproto.exe
@author
	Dany
*/
require_once("XByteArray.php");


	class XPACKET_OnCancelTimerResult
	{
		    public static  $_m_xcmd/*:int*/=_EMSG_LocalEvent::SMSG_OnCancelTimerResult;

	    
		public $errorCode/*:INT*/;

	    
	    public function XPACKET_OnCancelTimerResult()
		{
	        $this->errorCode =0;/*INT*/

		}
			
		public static function _Size($errorCode/*:INT*/ )
		{
			$__xv	= 0;
			$i		=0;

            $__xv +=4;//LENGHT
            $__xv +=4;//_m_xcmd
            $__xv +=4;//errorCode

			return $__xv;
		}
				
		public static function _ToBuffer($__dst/*XByteArray*/,$errorCode/*:INT*/ )
		{
			$__xv	= 0;
			$i		=0;

			$__dst->writeInt32(XPACKET_OnCancelTimerResult::_Size($errorCode/*:INT*/ ));
			$__xv +=4;
			$__dst->writeInt32(XPACKET_OnCancelTimerResult::$_m_xcmd);
			$__xv +=4;

            //Write codes of errorCode
            //
            $__dst->writeInt32($errorCode);
            $__xv +=4;

			return $__xv;
		}
		
		public static function _ClassFromParameters($errorCode/*:INT*/ )
		{
			$_class = new XPACKET_OnCancelTimerResult();

            $_class->errorCode=$errorCode;
			
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

            //Read codes of errorCode
            //
            if($__src->getBytesAvailable()>=4)
            {
                $this->errorCode=$__src->readInt32();
                $__xv +=4;
            }
            else
            {
                return 0;
            }

			return $__xv;
		}
		
		public function ToBuffer($__dst/*XByteArray*/)
		{
			return XPACKET_OnCancelTimerResult::_ToBuffer($__dst,$this->errorCode );
		}
		
		public function Size()
		{
			return XPACKET_OnCancelTimerResult::_Size($this->errorCode );
		}

    public  function FromXml(/*XP_XMLNODE_PTR*/ $pNode)
    {

        $this->errorCode = XFROM_XML($this->errorCode,$pNode,"errorCode",0,"");

		  	return 0;
    }
    
    public  function   ToXml(/*XSTRING_STREAM & out*/)
    {
        $__xv_out="";

        $__xv_out .= XTO_XML($this->errorCode,"errorCode",0, 0);

        return $__xv_out;
    }
    
    public   function fromAMFObject($pNode)
    {
       
        
        $this->errorCode = XFROM_AMFOBJECT($this->errorCode,$pNode,"errorCode",0,"");

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
    	if(XPACKET_OnCancelTimerResult::$_m_xcmd == _EMSG_ServerEvent::SMSG_OnSendZipData){
    		return "([ignore zip data])";
    	}
		
    	$__xv_out  = "(";
    	
        $__xv_out .= "errorCode=".$this->ParamDebugString($this->errorCode).",";

    	
    	$__xv_out  .= ")";
    	
    	$__xv_out = str_replace(",)",")",$__xv_out);
    	
    	return $__xv_out;
    }
    
   	public static function toAMFObject($__dst/*XByteArray*/,$errorCode/*:INT*/ )
		{
			$__xv	= 0;
			$i		=0;
      $obj = array();

        $obj["errorCode"]=$errorCode ;

      if(count($obj)>0)
      {
          $outBuffer  = WriteAMF3Object($obj);
          $__xv = strlen($outBuffer);
          $__xv+=8;
          $__dst->writeInt32($__xv);
          $__dst->writeInt32(XPACKET_OnCancelTimerResult::$_m_xcmd);
          $__dst->writeBinary($outBuffer,strlen($outBuffer));
      }
      else
      {
          $__xv =8;
          $__dst->writeInt32($__xv);
          $__dst->writeInt32(XPACKET_OnCancelTimerResult::$_m_xcmd);
      }
      
      
			return $__xv;
		}
	}
	
	
?>
