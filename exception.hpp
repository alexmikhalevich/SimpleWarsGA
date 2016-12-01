#include <string>

class IException {
	public:
		std::string what() const = 0;
};

class ExInitFailed : public IException {
	public:
		std::string what() const {
			return "[EE]: Failed to init SDL";
		}
};

class ExWindowCreationFailed : public IException {
	public:
		std::string what() const {
			return "[EE]: Failed to create window";
		}
};

class ExRendererCreationFailed : public IException {
	public:
		std::string what() const {
			return "[EE]: Failed to create renderer";
		}
};
