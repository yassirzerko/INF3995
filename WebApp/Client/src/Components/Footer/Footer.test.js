import React from "react";
import { mount, shallow } from "enzyme";
import { Footer } from "./Footer";

describe("Footer", () => {
  it("should render initial layout", () => {
    const component = shallow(<Footer />);
    expect(component.getElements()).toMatchSnapshot();
  });

  it("Should have a footer element", () => {
    const footer = mount(<Footer />);
    const element = footer.find("footer");
    expect(element).toBeDefined();
  });

  it("Should have the correct text", () => {
    const footer = mount(<Footer />);
    const text = footer.find("a");

    expect(text.text()).toEqual("Minimal Drone Swarm Navigation System");
  });
});
