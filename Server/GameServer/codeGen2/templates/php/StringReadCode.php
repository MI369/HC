
            //Read codes of /*FIELD_NAME*/
            //
            $__/*FIELD_NAME*/_szSize	= new XInteger();
            $this->/*FIELD_NAME*/ =XByteArray::/*READ_METHOD*/($__src,$__/*FIELD_NAME*/_szSize);
            if($__/*FIELD_NAME*/_szSize->_value<=0) 
                return 0;
            $__xv +=$__/*FIELD_NAME*/_szSize->_value;
