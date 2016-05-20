 /**
  * @file PMBUSStatus.h
  */

typedef struct pmbusStatus_t {

	pmbusStatus_t(){
		memset(this, 0, sizeof(pmbusStatus_t));
	}

	char m_currentPage;
	double m_vout_mode_exponent;

	double m_VIN;
	double m_IIN;
	
	double m_PIN;
	double m_POUT;

	double m_VOUT;
	double m_IOUT;

	double m_VoSBY;
	double m_IoSBY;

	double m_VCAP;
	double m_AMD_8D;

	double m_SEC_8E;
	double m_PRI_8F;

	double m_FAN1;
	double m_FAN2;

	double m_FAN3;
	double m_FAN4;


	double m_VIN_Max;
	double m_VIN_Min;
	char   m_VIN_Set;

	double m_IIN_Max;
	double m_IIN_Min;
	char   m_IIN_Set;

	double m_VCAP_Max;
	double m_VCAP_Min;
	char   m_VCAP_Set;

	double m_AMD_8D_Max;
	double m_AMD_8D_Min;
	char   m_AMD_8D_Set;

	double m_SEC_8E_Max;
	double m_SEC_8E_Min;
	char   m_SEC_8E_Set;

	double m_PRI_8F_Max;
	double m_PRI_8F_Min;
	char   m_PRI_8F_Set;

	double m_FAN1_Max;
	double m_FAN1_Min;
	char   m_FAN1_Set;

	double m_POUT_Max;
	double m_POUT_Min;
	char   m_POUT_Set;

	double m_PIN_Max;
	double m_PIN_Min;
	char   m_PIN_Set;

	double m_VOUT_Max;
	double m_VOUT_Min;
	char   m_VOUT_Set;

	double m_IOUT_Max;
	double m_IOUT_Min;
	char   m_IOUT_Set;

	double m_VoSBY_Max;
	double m_VoSBY_Min;
	char   m_VoSBY_Set;

	double m_IoSBY_Max;
	double m_IoSBY_Min;
	char   m_IoSBY_Set;


	void SaveIoSBY(double ioSBY){
		this->m_IoSBY = ioSBY;
		// Maximun
		if (this->m_IoSBY > this->m_IoSBY_Max){
			this->m_IoSBY_Max = this->m_IoSBY;
		}
		// Mininum
		if (this->m_IoSBY < this->m_IoSBY_Min || m_IoSBY_Set == 0){
			this->m_IoSBY_Min = this->m_IoSBY;
			m_IoSBY_Set = 1;
		}
	}

	void SaveVoSBY(double voSBY){
		this->m_VoSBY = voSBY;
		// Maximun
		if (this->m_VoSBY > this->m_VoSBY_Max){
			this->m_VoSBY_Max = this->m_VoSBY;
		}
		// Mininum
		if (this->m_VoSBY < this->m_VoSBY_Min || m_VoSBY_Set == 0){
			this->m_VoSBY_Min = this->m_VoSBY;
			m_VoSBY_Set = 1;
		}
	}

	void SaveIOUT(double iout){
		this->m_IOUT = iout;
		// Maximun
		if (this->m_IOUT > this->m_IOUT_Max){
			this->m_IOUT_Max = this->m_IOUT;
		}
		// Mininum
		if (this->m_IOUT < this->m_IOUT_Min || m_IOUT_Set == 0){
			this->m_IOUT_Min = this->m_IOUT;
			m_IOUT_Set = 1;
		}
	}

	void SaveVOUT(double vout){
		this->m_VOUT = vout;
		// Maximun
		if (this->m_VOUT > this->m_VOUT_Max){
			this->m_VOUT_Max = this->m_VOUT;
		}
		// Mininum
		if (this->m_VOUT < this->m_VOUT_Min || m_VOUT_Set == 0){
			this->m_VOUT_Min = this->m_VOUT;
			m_VOUT_Set = 1;
		}
	}

	void SaveVIN(double vin){
		this->m_VIN = vin;
		// Maximun
		if (this->m_VIN > this->m_VIN_Max){
			this->m_VIN_Max = this->m_VIN;
		}
		// Mininum
		if (this->m_VIN < this->m_VIN_Min || m_VIN_Set == 0){
			this->m_VIN_Min = this->m_VIN;
			m_VIN_Set = 1;
		}
	}

	void SaveIIN(double iin){
		this->m_IIN = iin;
		// Maximun
		if (this->m_IIN > this->m_IIN_Max){
			this->m_IIN_Max = this->m_IIN;
		}
		// Mininum
		if (this->m_IIN < this->m_IIN_Min || m_IIN_Set == 0){
			this->m_IIN_Min = this->m_IIN;
			m_IIN_Set = 1;
		}
	}

	void SaveVCAP(double vcap){
		this->m_VCAP = vcap;
		// Maximun
		if (this->m_VCAP > this->m_VCAP_Max){
			this->m_VCAP_Max = this->m_VCAP;
		}
		// Mininum
		if (this->m_VCAP < this->m_VCAP_Min || m_VCAP_Set == 0){
			this->m_VCAP_Min = this->m_VCAP;
			m_VCAP_Set = 1;
		}
	}

	void SaveAMD_8D(double amd8d){
		this->m_AMD_8D = amd8d;
		// Maximun
		if (this->m_AMD_8D > this->m_AMD_8D_Max){
			this->m_AMD_8D_Max = this->m_AMD_8D;
		}
		// Mininum
		if (this->m_AMD_8D < this->m_AMD_8D_Min || m_AMD_8D_Set == 0){
			this->m_AMD_8D_Min = this->m_AMD_8D;
			m_AMD_8D_Set = 1;
		}
	}

	void SaveSEC_8E(double sec8e){
		this->m_SEC_8E = sec8e;
		// Maximun
		if (this->m_SEC_8E > this->m_SEC_8E_Max){
			this->m_SEC_8E_Max = this->m_SEC_8E;
		}
		// Mininum
		if (this->m_SEC_8E < this->m_SEC_8E_Min || m_SEC_8E_Set == 0){
			this->m_SEC_8E_Min = this->m_SEC_8E;
			m_SEC_8E_Set = 1;
		}
	}

	void SavePRI_8F(double pri8f){
		this->m_PRI_8F = pri8f;
		// Maximun
		if (this->m_PRI_8F > this->m_PRI_8F_Max){
			this->m_PRI_8F_Max = this->m_PRI_8F;
		}
		// Mininum
		if (this->m_PRI_8F < this->m_PRI_8F_Min || m_PRI_8F_Set == 0){
			this->m_PRI_8F_Min = this->m_PRI_8F;
			m_PRI_8F_Set = 1;
		}
	}

	void SaveFAN1(double fan1){
		this->m_FAN1 = fan1;
		// Maximun
		if (this->m_FAN1 > this->m_FAN1_Max){
			this->m_FAN1_Max = this->m_FAN1;
		}
		// Mininum
		if (this->m_FAN1 < this->m_FAN1_Min || m_FAN1_Set == 0){
			this->m_FAN1_Min = this->m_FAN1;
			m_FAN1_Set = 1;
		}
	}

	void SavePOUT(double pout){
		this->m_POUT = pout;
		// Maximun
		if (this->m_POUT > this->m_POUT_Max){
			this->m_POUT_Max = this->m_POUT;
		}
		// Mininum
		if (this->m_POUT < this->m_POUT_Min || m_POUT_Set == 0){
			this->m_POUT_Min = this->m_POUT;
			m_POUT_Set = 1;
		}
	}

	void SavePIN(double pin){
		this->m_PIN = pin;
		// Maximun
		if (this->m_PIN > this->m_PIN_Max){
			this->m_PIN_Max = this->m_PIN;
		}
		// Mininum
		if (this->m_PIN < this->m_PIN_Min || m_PIN_Set == 0){
			this->m_PIN_Min = this->m_PIN;
			m_PIN_Set = 1;
		}
	}


} PMBUSSTATUS_t;