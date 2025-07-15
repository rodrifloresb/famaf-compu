package namedEntity;

/*Esta clase modela la nocion de entidad nombrada*/

public class NamedEntity {
	String name;
	String category;
	int frequency;

	public NamedEntity(String name, String category, int frequency) {
		super();
		this.name = name;
		this.category = category;
		this.frequency = frequency;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getCategory() {
		return name;
	}

	public void setCategory(String name) {
		this.name = name;
	}

	public int getFrequency() {
		return frequency;
	}

	public void setFrequency(int frequency) {
		this.frequency = frequency;
	}

	public void incFrequency() {
		this.frequency++;
	}

	@Override
	public String toString() {
		return "ObjectNamedEntity [name=" + name + ", frequency=" + frequency + "]";
	}

	public void prettyPrint() {
		if (this.category.equals("Company")) {
			System.out.println("\nCategoria: Compañias");
			System.out.println("Entidad:" + " " + this.getName() + "\nFrecuencia:" + " " + this.getFrequency());
		} else if (this.category.equals("Person")) {
			System.out.println("\nCategoria: Personas");
			System.out.println("Entidad:" + " " + this.getName() + "\nFrecuencia:" + " " + this.getFrequency());
		} else if (this.category.equals("Country")) {
			System.out.println("\nCategoria: Paises");
			System.out.println("Entidad:" + " " + this.getName() + "\nFrecuencia:" + " " + this.getFrequency());
		} else {
			System.out.println("\nCategoria: Otro");
			System.out.println("Entidad:" + " " + this.getName() + "\nFrecuencia:" + " " + this.getFrequency());
		}

	}

}
