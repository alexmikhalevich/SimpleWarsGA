#include <string>

class IException {
	public:
		virtual std::string what() const = 0;
};

class ExInitFailed : public IException {
	private:
		std::string m_error;
	public:
		ExInitFailed(const std::string& error) : m_error(error) {}
		std::string what() const {
			return "[EE]: Failed to init SDL: " + m_error;
		}
};

class ExWindowCreationFailed : public IException {
	private:
		std::string m_error;
	public:
		ExWindowCreationFailed(const std::string& error) : m_error(error) {}
		std::string what() const {
			return "[EE]: Failed to create window: " + m_error;
		}
};

class ExRendererCreationFailed : public IException {
	private:
		std::string m_error;
	public:
		ExRendererCreationFailed(const std::string& error) : m_error(error) {}
		std::string what() const {
			return "[EE]: Failed to create renderer: " + m_error;
		}
};

class ExInvalidUnit : public IException {
	private:
		std::string m_error;
	public:
		ExInvalidUnit(const std::string& error) m_error(error) {}
		std::string what() const {
			return "[EE]: Invalid unit: " + m_error;
		}
};
